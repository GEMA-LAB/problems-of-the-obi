"""Construtor e exportador de dataset para questoes com solucao em Python."""
import json
import shutil
from pathlib import Path
from typing import Dict, List, Optional, Tuple


class PythonDatasetBuilder:
    """Extrai e gera dataset derivado filtrando questoes que possuem codigo em Python."""

    PYTHON_EXTENSIONS = {".py", ".py3"}

    def is_python_file(self, path: Path) -> bool:
        """Verifica se a extensao do arquivo corresponde a Python."""
        return Path(path).suffix.lower() in self.PYTHON_EXTENSIONS

    def has_python_solution(self, question_dir: Path) -> Tuple[bool, List[Path]]:
        """
        Verifica se o diretorio da questao possui solucoes em Python.
        Retorna uma tupla (possui_python, lista_arquivos_python).
        """
        solutions_dir = Path(question_dir) / "solutions"
        if not solutions_dir.exists() or not solutions_dir.is_dir():
            return False, []

        python_files = [
            f for f in solutions_dir.iterdir()
            if f.is_file() and self.is_python_file(f)
        ]
        return len(python_files) > 0, python_files

    def export_question(self, source_question_dir: Path, target_question_dir: Path) -> Dict[str, int | bool]:
        """
        Exporta uma questao unica para o destino:
        - Copia problem.json
        - Copia test_cases/
        - Copia exclusivamente arquivos de solucao em Python para solutions/
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

        # 3. Copia apenas solucoes em Python
        target_solutions = target_dir / "solutions"
        target_solutions.mkdir(parents=True, exist_ok=True)

        has_py, py_files = self.has_python_solution(source_dir)
        for py_file in py_files:
            shutil.copy2(py_file, target_solutions / py_file.name)

        return {
            "sucesso": True,
            "arquivos_python": len(py_files),
            "casos_teste": test_cases_count,
        }

    def build_dataset(
        self,
        source_dir: Path,
        target_dir: Path,
        ano_filtro: Optional[int] = None,
        nivel_filtro: Optional[str] = None,
        force: bool = False,
    ) -> Dict[str, int]:
        """
        Varre o diretorio de origem e gera o dataset filtrado no diretorio de destino.
        """
        source_dir = Path(source_dir)
        target_dir = Path(target_dir)

        if not source_dir.exists():
            return {
                "total_questoes_analisadas": 0,
                "questoes_com_python": 0,
                "questoes_exportadas": 0,
                "total_arquivos_python": 0,
                "total_casos_teste": 0,
            }

        target_dir.mkdir(parents=True, exist_ok=True)

        stats = {
            "total_questoes_analisadas": 0,
            "questoes_com_python": 0,
            "questoes_exportadas": 0,
            "total_arquivos_python": 0,
            "total_casos_teste": 0,
        }

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

            has_py, py_files = self.has_python_solution(q_dir)
            if not has_py:
                continue

            stats["questoes_com_python"] += 1

            dest_question_dir = target_dir.joinpath(*rel_parts)

            # Idempotencia: pula se ja existe e nao for force
            if dest_question_dir.exists() and not force:
                dest_sol = dest_question_dir / "solutions"
                if dest_sol.exists() and any(self.is_python_file(f) for f in dest_sol.iterdir() if f.is_file()):
                    stats["questoes_exportadas"] += 1
                    stats["total_arquivos_python"] += len(py_files)
                    continue

            export_stats = self.export_question(q_dir, dest_question_dir)
            stats["questoes_exportadas"] += 1
            stats["total_arquivos_python"] += int(export_stats["arquivos_python"])
            stats["total_casos_teste"] += int(export_stats["casos_teste"])

        return stats
