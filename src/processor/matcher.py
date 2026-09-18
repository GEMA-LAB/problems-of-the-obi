"""Modulo de normalizacao Unicode e correspondencia de recursos."""
import json
import re
import unicodedata
from pathlib import Path
from typing import List, Optional
from src.core.config import DEFAULT_CODIGO_DIR, DEFAULT_GABARITOS_DIR, MAPEAMENTO_LINGUAGEM
from src.models.test_case import QuestionFolder, SolutionSource, TestCaseSource

STOPWORDS_PT = {
    "a", "o", "as", "os", "de", "da", "do", "das", "dos",
    "em", "no", "na", "nos", "nas", "e", "ou", "com", "para",
    "por", "um", "uma", "uns", "umas", "ao", "aos",
}

TECHNICAL_TOKENS = {
    "solucao", "sol", "reference", "ref", "aluno", "teste", "test",
    "c", "cpp", "py", "py3", "java", "js", "pas", "zip",
    "sorting", "union", "find", "andre", "bez", "bezrutchka", "lobo", "pedro",
    "matriz", "dict", "freq", "map", "bb", "brute", "while", "mrk", "repr", "carol", "rafael",
}


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



def get_tokens(text: str) -> list[str]:
    """Extrai tokens normalizados divididos por espacos, tracos ou sublinhados."""
    parts = re.split(r"[\s_\-]+", text)
    tokens = []
    for p in parts:
        norm = normalize_name(p)
        if norm:
            tokens.append(norm)
    return tokens


def calculate_solution_match_score(
    question_title: str,
    file_stem: str,
    alias: Optional[str] = None,
) -> int:
    """
    Calcula pontuacao de correspondencia heuristica (0 a 100):
    100: Exatidao normalizada
    95:  Alias explicito
    80-95: Intersecao completa de tokens sem stopwords
    75:  Slug reverso (file_stem comeca com target_slug)
    50-70: Prefixo por separador (_ ou -)
    0:   Nao corresponde
    """
    target_slug = normalize_name(question_title)
    stem_norm = normalize_name(file_stem)
    alias_slug = normalize_name(alias) if alias else ""

    if not target_slug or not stem_norm:
        return 0

    if stem_norm == target_slug:
        return 100

    if alias_slug and (stem_norm == alias_slug or alias_slug in stem_norm):
        return 95

    q_tokens = [w for w in get_tokens(question_title) if w not in STOPWORDS_PT]
    f_tokens = get_tokens(file_stem)

    # Intersecao completa dos tokens significativos da questao
    if q_tokens and all(qt in f_tokens for qt in q_tokens):
        return 80 + min(len(q_tokens) * 5, 15)

    # Reverse slug: stem_norm starts with target_slug (ex: recargacarro)
    if stem_norm.startswith(target_slug) and len(target_slug) >= 3:
        return 75

    # Prefixo antes de separador
    if f_tokens:
        first_token = f_tokens[0]
        if len(first_token) >= 3:
            if first_token == target_slug:
                return 70
            if target_slug.startswith(first_token):
                matched_tokens = sum(1 for qt in q_tokens if qt in f_tokens)
                return 50 + min(matched_tokens * 10, 20)

    return 0


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
        Busca arquivos de codigo ou zips de solucao oficial para a questao
        utilizando correspondencia heuristica em 4 camadas e desambiguacao por especificidade.
        """
        if not self.codigo_dir.exists():
            return []

        busca_caminhos = []
        path_nivel = self.codigo_dir / str(question.ano) / question.nivel.lower()
        if path_nivel.exists():
            busca_caminhos.append(path_nivel)
        path_ano = self.codigo_dir / str(question.ano)
        if path_ano.exists() and path_ano not in busca_caminhos:
            busca_caminhos.append(path_ano)

        solutions: List[SolutionSource] = []
        arquivos_vistos = set()

        # Coleta irmaos para desambiguacao se pasta da questao estiver disponivel
        sibling_titles: List[str] = []
        if question.path and question.path.parent and question.path.parent.exists():
            for sibling_dir in question.path.parent.iterdir():
                if sibling_dir.is_dir() and sibling_dir != question.path:
                    prob_file = sibling_dir / "problem.json"
                    s_title = sibling_dir.name
                    if prob_file.exists():
                        try:
                            data = json.loads(prob_file.read_text(encoding="utf-8"))
                            s_title = data.get("title", s_title)
                        except Exception:
                            pass
                    sibling_titles.append(s_title)

        for pasta in busca_caminhos:
            for item in pasta.rglob("*"):
                if item.is_file() and item not in arquivos_vistos:
                    stem_norm = normalize_name(item.stem)
                    ext = item.suffix.lower()

                    score = calculate_solution_match_score(
                        question.titulo, item.stem, alias=matcher_alias
                    )
                    if score <= 0:
                        continue

                    # Desambiguacao contra questoes irmas no mesmo nivel
                    is_better_for_sibling = False
                    for s_title in sibling_titles:
                        s_score = calculate_solution_match_score(s_title, item.stem)
                        if s_score > score:
                            is_better_for_sibling = True
                            break

                    if is_better_for_sibling:
                        continue

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
