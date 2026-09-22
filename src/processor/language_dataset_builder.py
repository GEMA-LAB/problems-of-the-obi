"""Construtor e exportador de datasets por linguagem de programacao."""
import json
import shutil
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple

# Mapeamento de configuracoes canonicas por linguagem
SUPPORTED_LANGUAGES: Dict[str, Dict[str, any]] = {
    "python": {
        "canonical": "python",
        "extensions": {".py", ".py3"},
        "default_dir_name": "dataset_obi_python",
        "aliases": {"python", "py", "py3"},
    },
    "cpp": {
        "canonical": "cpp",
        "extensions": {".cpp", ".cc", ".cxx"},
        "default_dir_name": "dataset_obi_cpp",
        "aliases": {"cpp", "c++", "cc", "cxx"},
    },
    "c": {
        "canonical": "c",
        "extensions": {".c"},
        "default_dir_name": "dataset_obi_c",
        "aliases": {"c"},
    },
    "java": {
        "canonical": "java",
        "extensions": {".java"},
        "default_dir_name": "dataset_obi_java",
        "aliases": {"java"},
    },
    "pascal": {
        "canonical": "pascal",
        "extensions": {".pas"},
        "default_dir_name": "dataset_obi_pascal",
        "aliases": {"pascal", "pas"},
    },
    "javascript": {
        "canonical": "javascript",
        "extensions": {".js"},
        "default_dir_name": "dataset_obi_javascript",
        "aliases": {"javascript", "js"},
    },
}


class LanguageDatasetBuilder:
    """Extrai e gera dataset derivado filtrando questoes por linguagem de programacao."""

    @classmethod
    def normalize_language(cls, lang: str) -> str:
        """
        Normaliza o identificador da linguagem para a chave canonica.
        Lanca ValueError se a linguagem nao for suportada.
        """
        if not lang:
            return "python"

        lang_clean = lang.strip().lower()
        for canonical, config in SUPPORTED_LANGUAGES.items():
            if lang_clean in config["aliases"]:
                return canonical

        raise ValueError(
            f"Linguagem '{lang}' nao suportada. Opcoes validas: "
            f"{', '.join(sorted(SUPPORTED_LANGUAGES.keys()))}"
        )

    @classmethod
    def get_language_extensions(cls, lang: str) -> Set[str]:
        """Retorna o conjunto de extensoes correspondentes a linguagem."""
        canonical = cls.normalize_language(lang)
        return SUPPORTED_LANGUAGES[canonical]["extensions"]

    @classmethod
    def get_default_target_dir(cls, lang: str) -> Path:
        """Retorna o caminho padrao do diretorio de saida para a linguagem."""
        canonical = cls.normalize_language(lang)
        dir_name = SUPPORTED_LANGUAGES[canonical]["default_dir_name"]
        return Path(dir_name)

    def is_language_file(self, path: Path, lang: str) -> bool:
        """Verifica se a extensao do arquivo corresponde a linguagem indicada."""
        exts = self.get_language_extensions(lang)
        return Path(path).suffix.lower() in exts

    def has_language_solution(self, question_dir: Path, lang: str) -> Tuple[bool, List[Path]]:
        """
        Verifica se o diretorio da questao possui solucoes na linguagem especificada.
        Retorna uma tupla (possui_solucao, lista_arquivos).
        """
        solutions_dir = Path(question_dir) / "solutions"
        if not solutions_dir.exists() or not solutions_dir.is_dir():
            return False, []

        valid_files = [
            f for f in solutions_dir.iterdir()
            if f.is_file() and self.is_language_file(f, lang)
        ]
        return len(valid_files) > 0, valid_files

    def export_question(
        self,
        source_question_dir: Path,
        target_question_dir: Path,
        lang: str = "python",
    ) -> Dict[str, int | bool]:
        """
        Exporta uma questao unica para o destino:
        - Copia problem.json
        - Copia test_cases/
        - Copia exclusivamente arquivos de solucao da linguagem para solutions/
        """
        source_dir = Path(source_question_dir)
        target_dir = Path(target_question_dir)

        target_dir.mkdir(parents=True, exist_ok=True)

        # 1. Copia problem.json
        prob_json = source_dir / "problem.json"
        if prob_json.exists():
            shutil.copy2(prob_json, target_dir / "problem.json")

        # 2. Copia test_cases/
        source_tests = source_dir / "test_cases"
        target_tests = target_dir / "test_cases"
        test_cases_count = 0
        if source_tests.exists() and source_tests.is_dir():
            if target_tests.exists():
                shutil.rmtree(target_tests)
            shutil.copytree(source_tests, target_tests)
            test_cases_count = len([f for f in target_tests.rglob("*") if f.is_file()])

        # 3. Copia apenas solucoes da linguagem solicitada
        target_solutions = target_dir / "solutions"
        target_solutions.mkdir(parents=True, exist_ok=True)

        has_sol, sol_files = self.has_language_solution(source_dir, lang)
        for sol_file in sol_files:
            shutil.copy2(sol_file, target_solutions / sol_file.name)

        return {
            "sucesso": True,
            "arquivos_solucao": len(sol_files),
            "casos_teste": test_cases_count,
        }

    def build_dataset(
        self,
        source_dir: Path,
        target_dir: Optional[Path] = None,
        language: str = "python",
        ano_filtro: Optional[int] = None,
        nivel_filtro: Optional[str] = None,
        force: bool = False,
    ) -> Dict[str, int | str]:
        """
        Varre o diretorio de origem e gera o dataset filtrado no diretorio de destino para a linguagem.
        """
        canonical_lang = self.normalize_language(language)
        source_dir = Path(source_dir)
        target_dir = Path(target_dir) if target_dir is not None else self.get_default_target_dir(canonical_lang)

        stats: Dict[str, int | str] = {
            "linguagem": canonical_lang,
            "diretorio_destino": str(target_dir),
            "total_questoes_analisadas": 0,
            "questoes_com_solucao": 0,
            "questoes_exportadas": 0,
            "total_arquivos_solucao": 0,
            "total_casos_teste": 0,
        }

        if not source_dir.exists():
            return stats

        target_dir.mkdir(parents=True, exist_ok=True)

        for json_path in source_dir.rglob("problem.json"):
            q_dir = json_path.parent

            # Obter partes relativas: [ano]/[nivel]/[nome_questao]
            try:
                rel_parts = q_dir.relative_to(source_dir).parts
            except ValueError:
                continue

            if len(rel_parts) < 3:
                continue

            ano_str, nivel_str = rel_parts[0], rel_parts[1]

            # Filtros opcionais
            if ano_filtro is not None and str(ano_filtro) != ano_str:
                continue
            if nivel_filtro is not None and nivel_filtro.lower() != nivel_str.lower():
                continue

            stats["total_questoes_analisadas"] += 1

            has_sol, sol_files = self.has_language_solution(q_dir, canonical_lang)
            if not has_sol:
                continue

            stats["questoes_com_solucao"] += 1

            dest_question_dir = target_dir.joinpath(*rel_parts)

            # Idempotencia: pula se ja existe e nao for force
            if dest_question_dir.exists() and not force:
                dest_sol = dest_question_dir / "solutions"
                if dest_sol.exists() and any(self.is_language_file(f, canonical_lang) for f in dest_sol.iterdir() if f.is_file()):
                    stats["questoes_exportadas"] += 1
                    stats["total_arquivos_solucao"] += len(sol_files)
                    continue

            export_stats = self.export_question(q_dir, dest_question_dir, canonical_lang)
            stats["questoes_exportadas"] += 1
            stats["total_arquivos_solucao"] += int(export_stats["arquivos_solucao"])
            stats["total_casos_teste"] += int(export_stats["casos_teste"])

        return stats
