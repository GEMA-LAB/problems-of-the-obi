"""Modulo de normalizacao Unicode e correspondencia de recursos."""
import re
import unicodedata
from pathlib import Path
from typing import List, Optional
from src.core.config import DEFAULT_CODIGO_DIR, DEFAULT_GABARITOS_DIR, MAPEAMENTO_LINGUAGEM
from src.models.test_case import QuestionFolder, SolutionSource, TestCaseSource


def normalize_name(name: str) -> str:
    """
    Normaliza uma string para correspondencia estrita de nomes:
    - Decomposicao canonica Unicode NFD
    - Remocao de diacriticos e acentos
    - Conversao para minusculas
    - Remocao de pontuacoes, tracos, sublinhados e espacos
    - Mantem apenas caracteres alfanumericos [a-z] e [0-9]
    """
    if not name:
        return ""
    nfd = unicodedata.normalize("NFD", name)
    sem_acento = "".join(c for c in nfd if unicodedata.category(c) != "Mn")
    return re.sub(r"[^a-z0-9]", "", sem_acento.lower()).strip()



class ResourceMatcher:

    """Localiza arquivos de gabarito e codigos de solucao oficial de forma resiliente."""

    def __init__(
        self,
        gabaritos_dir: Path = DEFAULT_GABARITOS_DIR,
        codigo_dir: Path = DEFAULT_CODIGO_DIR,
    ):
        self.gabaritos_dir = Path(gabaritos_dir)
        self.codigo_dir = Path(codigo_dir)

    def find_gabarito(self, question: QuestionFolder) -> Optional[TestCaseSource]:
        """
        Busca o arquivo .zip de gabarito correspondente a questao.
        Prioriza ano e nivel; caso nao encontre, busca pelo ano e name_norm.
        """
        if not self.gabaritos_dir.exists():
            return None

        target_slug = question.titulo_normalizado

        # 1. Busca em gabaritos/[ano]/[nivel]/
        path_nivel = self.gabaritos_dir / str(question.ano) / question.nivel.lower()
        if path_nivel.exists():
            for zip_file in path_nivel.glob("*.zip"):
                if normalize_name(zip_file.stem) == target_slug:
                    return TestCaseSource(
                        path_zip=zip_file,
                        ano=question.ano,
                        nivel=question.nivel.lower(),
                        nome_normalizado=normalize_name(zip_file.stem),
                    )

        # 2, Busca em gabaritos/[ano]/ recursivo
        path_ano = self.gabaritos_dir / str(question.ano)
        if path_ano.exists():
            for zip_file in path_ano.rglob("*.zip"):
                stem_slug = normalize_name(zip_file.stem)
                if stem_slug == target_slug:
                    return TestCaseSource(
                        path_zip=zip_file,
                        ano=question.ano,
                        nivel=zip_file.parent.name.lower(),
                        nome_normalizado=stem_slug,
                    )

        # 3. Correspondencia parcial (quando o zip contem ou e substring do titulo)
        if path_ano.exists():
            for zip_file in path_ano.rglob("*.zip"):
                stem_slug = normalize_name(zip_file.stem)
                if stem_slug and len(stem_slug) >= 4 and (stem_slug in target_slug or target_slug in stem_slug):
                    return TestCaseSource(
                        path_zip=zip_file,
                        ano=question.ano,
                        nivel=zip_file.parent.name.lower(),
                        nome_normalizado=stem_slug,
                    )

        return None

    def find_solutions(
        self,
        question: QuestionFolder,
        matcher_alias: Optional[str] = None,
    ) -> List[SolutionSource]:
        """
        Busca arquivos de codigo ou zips de solucao oficial para a questao.
        """
        if not self.codigo_dir.exists():
            return []

        target_slug = question.titulo_normalizado
        alias_slug = normalize_name(matcher_alias) if matcher_alias else ""

        busca_caminhos = []
        path_nivel = self.codigo_dir / str(question.ano) / question.nivel.lower()
        if path_nivel.exists():
            busca_caminhos.append(path_nivel)
        path_ano = self.codigo_dir / str(question.ano)
        if path_ano.exists() and path_ano not in busca_caminhos:
            busca_caminhos.append(path_ano)

        solutions: List[SolutionSource] = []
        arquivos_vistos = set()

        for pasta in busca_caminhos:
            for item in pasta.rglob("*"):
                if item.is_file() and item not in arquivos_vistos:
                    stem_norm = normalize_name(item.stem)
                    ext = item.suffix.lower()

                    matches = False
                    if stem_norm == target_slug:
                        matches = True
                    elif alias_slug and (stem_norm == alias_slug or alias_slug in stem_norm):
                        matches = True
                    elif stem_norm and len(stem_norm) >= 3 and (stem_norm in target_slug or target_slug.startswith(stem_norm)):
                        matches = True

                    if matches:
                        arquivos_vistos.add(item)
                        linguagem = MAPEAMENTO_LINGUAGEM.get(ext, ext.replace(".", ""))
                        solutions.append(
                            SolutionSource(
                                path_arquivo=item,
                                ano=question.ano,
                                nivel=question.nivel.lower(),
                                nome_normalizado=stem_norm,
                                linguagem=linguagem,
                            )
                        )

        return solutions
