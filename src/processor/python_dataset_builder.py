"""Construtor e exportador de dataset para questoes com solucao em Python."""
from pathlib import Path
from typing import Dict, List, Optional, Tuple
from src.processor.language_dataset_builder import LanguageDatasetBuilder


class PythonDatasetBuilder(LanguageDatasetBuilder):
    """Subclasse de LanguageDatasetBuilder especializada em Python para retrocompatibilidade."""

    PYTHON_EXTENSIONS = {".py", ".py3"}

    def is_python_file(self, path: Path) -> bool:
        """Verifica se a extensao do arquivo corresponde a Python."""
        return self.is_language_file(path, "python")

    def has_python_solution(self, question_dir: Path) -> Tuple[bool, List[Path]]:
        """Verifica se o diretorio da questao possui solucoes em Python."""
        return self.has_language_solution(question_dir, "python")

    def export_question(self, source_question_dir: Path, target_question_dir: Path, lang: str = "python") -> Dict[str, int | bool]:
        """Exporta uma questao unica para o destino."""
        res = super().export_question(source_question_dir, target_question_dir, lang=lang)
        return {
            "sucesso": res["sucesso"],
            "arquivos_solucao": res["arquivos_solucao"],
            "arquivos_python": res["arquivos_solucao"],
            "casos_teste": res["casos_teste"],
        }

    def build_dataset(
        self,
        source_dir: Path,
        target_dir: Path,
        ano_filtro: Optional[int] = None,
        nivel_filtro: Optional[str] = None,
        force: bool = False,
    ) -> Dict[str, int]:
        """Varre o diretorio de origem e gera o dataset filtrado no diretorio de destino."""
        stats = super().build_dataset(
            source_dir=source_dir,
            target_dir=target_dir,
            language="python",
            ano_filtro=ano_filtro,
            nivel_filtro=nivel_filtro,
            force=force,
        )
        return {
            "total_questoes_analisadas": stats["total_questoes_analisadas"],
            "questoes_com_python": stats["questoes_com_solucao"],
            "questoes_exportadas": stats["questoes_exportadas"],
            "total_arquivos_python": stats["total_arquivos_solucao"],
            "total_casos_teste": stats["total_casos_teste"],
        }
