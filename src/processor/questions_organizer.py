"""Modulo orquestrador para organizacao de questoes, gabaritos e solucoes."""
import json
import shutil
import tempfile
from pathlib import Path
from typing import Any, Dict, List, Optional
from src.core.config import DEFAULT_OUTPUT_DIR, OrganizeConfig
from src.models.test_case import (
    OrganizeResult,
    QuestionFolder,
    TestCasePair,
)
from src.processor.cleaner import DatasetCleaner
from src.processor.matcher import ResourceMatcher, normalize_name
from src.processor.normalizer import TestCaseNormalizer
from src.processor.zip_extractor import ZipExtractor


class QuestionsOrganizer:
    """Orquestrador do processo de associacao, descompactacao, normalizacao e limpeza."""

    def __init__(
        self,
        matcher: Optional[ResourceMatcher] = None,
        zip_extractor: Optional[ZipExtractor] = None,
        normalizer: Optional[TestCaseNormalizer] = None,
        cleaner: Optional[DatasetCleaner] = None,
    ):
        self.matcher = matcher or ResourceMatcher()
        self.zip_extractor = zip_extractor or ZipExtractor()
        self.normalizer = normalizer or TestCaseNormalizer()
        self.cleaner = cleaner or DatasetCleaner()

    def discover_questions(
        self,
        output_dir: Path = DEFAULT_OUTPUT_DIR,
        ano_filtro: Optional[int] = None,
        nivel_filtro: Optional[str] = None,
    ) -> List[QuestionFolder]:
        """
        Descobre questoes no diretorio de output atraves da presenca de problem.json.
        Aplica filtros opcionais por ano e nivel.
        """
        output_dir = Path(output_dir)
        if not output_dir.exists():
            return []

        questions: List[QuestionFolder] = []

        for json_file in output_dir.rglob("problem.json"):
            q_path = json_file.parent
            ano: Optional[int] = None
            nivel: str = ""
            titulo: str = ""

            try:
                data = json.loads(json_file.read_text(encoding="utf-8"))
                titulo = str(data.get("title", data.get("titulo", q_path.name))).strip()

                raw_year = data.get("year", data.get("ano", ""))
                if str(raw_year).isdigit():
                    ano = int(raw_year)

                nivel = str(data.get("level", data.get("nivel", ""))).strip().lower()
            except Exception:
                titulo = q_path.name

            # Se ano ou nivel nao foram extraidos do JSON, tenta inferir das partes do caminho
            try:
                rel_parts = q_path.relative_to(output_dir).parts
            except ValueError:
                rel_parts = q_path.parts

            if ano is None:
                for part in rel_parts:
                    if part.isdigit() and 1999 <= int(part) <= 2030:
                        ano = int(part)
                        break

            if not nivel:
                for part in rel_parts:
                    part_lower = part.lower()
                    if part_lower in ("pj", "p1", "p2", "senior", "geral", "iniciacao", "cfobi"):
                        nivel = part_lower
                        break

            ano = ano or 2024
            nivel = nivel or "geral"

            # Aplica filtros
            if ano_filtro is not None and ano != ano_filtro:
                continue
            if nivel_filtro is not None and nivel.lower() != nivel_filtro.lower():
                continue

            questions.append(
                QuestionFolder(
                    path=q_path,
                    ano=ano,
                    nivel=nivel,
                    titulo=titulo,
                    titulo_normalizado=normalize_name(titulo),
                )
            )

        questions.sort(key=lambda q: (q.ano, q.nivel, q.titulo))
        return questions

    def organize_question(
        self,
        question: QuestionFolder,
        config: OrganizeConfig,
    ) -> OrganizeResult:
        """
        Executa o fluxo completo de organizacao para uma questao:
        1. Idempotencia: pula se test_cases/inputs tiver testes e not config.force.
        2. Localiza e descompacta gabarito (.zip) em area temporaria.
        3. Normaliza pares sequenciais 1-para-1 em inputs/ e outputs/.
        4. Limpa residuos compilados e lixo em test_cases/.
        5. Copia e/ou extrai solucoes oficiais para solutions/.
        6. Se nao possuir testes validos, expurga a pasta da questao.
        """
        self.matcher.gabaritos_dir = config.pasta_gabaritos
        self.matcher.codigo_dir = config.pasta_codigo

        test_cases_dir = question.path / "test_cases"
        inputs_dir = test_cases_dir / "inputs"


        # 1. Verificacao de Idempotencia (Regra R3)
        if not config.force and inputs_dir.exists():
            existing_inputs = list(inputs_dir.glob("*.in"))
            if len(existing_inputs) > 0:
                # Garante que arquivos soltos na raiz de test_cases/ sejam limpos
                for item in list(test_cases_dir.iterdir()):
                    if item.is_file():
                        item.unlink(missing_ok=True)
                return OrganizeResult(
                    questao=question.titulo,
                    status="ignorado_idempotente",
                    mensagem="Testes ja normalizados existentes (force=False)",
                )

        # 2. Localizacao de gabarito
        gabarito_source = self.matcher.find_gabarito(question)
        normalized_pairs: List[TestCasePair] = []

        if gabarito_source and gabarito_source.path_zip.exists():
            with tempfile.TemporaryDirectory() as temp_dir:
                temp_path = Path(temp_dir)
                success = self.zip_extractor.extract_test_cases(
                    gabarito_source.path_zip, temp_path
                )
                if success:
                    raw_pairs = self.normalizer.scan_and_pair(temp_path)
                    if raw_pairs:
                        normalized_pairs = self.normalizer.normalize_to_destination(
                            raw_pairs, test_cases_dir
                        )
                        self.cleaner.clean_test_cases_residuals(
                            test_cases_dir, normalized_pairs
                        )

        # Se nao descompactou ou nao encontrou via gabaritos/, verifica se ja havia testes brutos na propria questao
        if not normalized_pairs and test_cases_dir.exists():
            raw_pairs = self.normalizer.scan_and_pair(test_cases_dir)
            if raw_pairs:
                normalized_pairs = self.normalizer.normalize_to_destination(
                    raw_pairs, test_cases_dir
                )
                self.cleaner.clean_test_cases_residuals(
                    test_cases_dir, normalized_pairs
                )

        # 3. Solucoes Oficiais (Regra R6, I3)
        solutions_count = 0
        solutions = self.matcher.find_solutions(question)
        if solutions:
            solutions_dir = question.path / "solutions"
            solutions_dir.mkdir(parents=True, exist_ok=True)
            for sol in solutions:
                if sol.path_arquivo.suffix.lower() == ".zip":
                    extracted = self.zip_extractor.extract_solutions(
                        sol.path_arquivo, solutions_dir
                    )
                    solutions_count += len(extracted)
                else:
                    dest_file = solutions_dir / sol.path_arquivo.name
                    shutil.copy2(sol.path_arquivo, dest_file)
                    solutions_count += 1

        # 4. Validacao e Expurgo Final (Regras R7, I1, I4)
        kept = self.cleaner.validate_and_cleanup_question(
            question.path, normalized_pairs
        )

        if not kept:
            return OrganizeResult(
                questao=question.titulo,
                status="removido_sem_testes",
                mensagem="Questao removida por ausencia de casos de teste validos",
            )

        status = "sucesso" if solutions_count > 0 else "parcial"
        return OrganizeResult(
            questao=question.titulo,
            test_pairs=normalized_pairs,
            solutions_count=solutions_count,
            status=status,
            mensagem="Organizada com sucesso",
        )

    def organize_all(
        self,
        config: OrganizeConfig,
        ano_filtro: Optional[int] = None,
        nivel_filtro: Optional[str] = None,
    ) -> Dict[str, Any]:
        """Executa a organizacao completa de todas as questoes descobertas e agrega estatisticas."""
        self.matcher.gabaritos_dir = config.pasta_gabaritos
        self.matcher.codigo_dir = config.pasta_codigo

        questions = self.discover_questions(
            output_dir=config.pasta_output,
            ano_filtro=ano_filtro,
            nivel_filtro=nivel_filtro,
        )

        stats = {
            "total_encontradas": len(questions),
            "sucesso": 0,
            "parcial": 0,
            "ignoradas_idempotentes": 0,
            "removidas_sem_testes": 0,
            "total_testes": 0,
            "total_solucoes": 0,
        }

        for q in questions:
            result = self.organize_question(q, config)
            if result.status == "sucesso":
                stats["sucesso"] += 1
            elif result.status == "parcial":
                stats["parcial"] += 1
            elif result.status == "ignorado_idempotente":
                stats["ignoradas_idempotentes"] += 1
            elif result.status == "removido_sem_testes":
                stats["removidas_sem_testes"] += 1

            stats["total_testes"] += len(result.test_pairs)
            stats["total_solucoes"] += result.solutions_count

        return stats
