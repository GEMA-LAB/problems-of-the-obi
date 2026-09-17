"""HTML parser and link extractor for OBI past exams."""
import re
from dataclasses import dataclass
from pathlib import Path
from typing import Optional
from urllib.parse import urljoin
from bs4 import BeautifulSoup



from src.core.config import EXTENSOES_CODIGO, MAPEAMENTO_LINGUAGEM, TERMOS_GABARITO


@dataclass(frozen=True)
class CadernoLink:
    """Represents a discovered exam PDF link."""
    url: str
    nome_arquivo: str
    ano: int
    nivel: str
    texto_link: str


@dataclass(frozen=True)
class CodigoSolucao:
    """Representa um codigo-fonte ou solucao oficial descoberta."""
    ano: int
    nivel: str
    nome_problema: str
    linguagem: str
    url: str
    nome_arquivo: str
    caminho_local: Optional[Path] = None
    texto_link: str = ""


@dataclass(frozen=True)
class GabaritoZIP:
    """Representa um arquivo compactado (.zip) de gabarito ou casos de teste."""
    ano: int
    nivel: str
    nome_questao: str
    url: str
    caminho_local: Optional[Path] = None
    texto_link: str = ""


class ObiScraper:
    """Scraper for OBI past competition pages."""

    def infer_level_from_solution_url(self, url_path: str) -> Optional[str]:
        """Infers competition level specifically from OBI solution directory pattern."""
        # Padrao: /solucoes/{ano}f{fase}{nivel}_{problema}/
        match = re.search(r"/solucoes/[^/]*?f\d+([a-z0-9]+)_", url_path.lower())
        if match:
            code = match.group(1)
            if code in ("pj", "p0", "junior"):
                return "pj"
            if code in ("p1", "nivel1", "1"):
                return "p1"
            if code in ("p2", "nivel2", "2"):
                return "p2"
            if code in ("ps", "pu", "senior", "sen", "s"):
                return "senior"
        return None

    def infer_level_or_phase(self, url_path: str, link_text: str, filename: str) -> str:
        """Infers the competition level (e.g., pj, p1, p2, senior) or phase from metadata."""
        # 1. Se for uma URL de solucao com diretorio estruturado da OBI
        sol_level = self.infer_level_from_solution_url(url_path)
        if sol_level:
            return sol_level

        # 2. Remover esquema e host para evitar falsos positivos com 'https'
        clean_text = re.sub(r"https?://[^\s/]+", "", f"{url_path} {link_text} {filename}").lower()

        # Checagem de níveis específicos
        # Júnior
        if any(term in clean_text for term in ["júnior", "junior", "nível júnior", "nivel junior"]) or \
           re.search(r"(?:f\d+|_|\b)(?:pj|p0)(?:_|\.|\b)", clean_text):
            return "pj"

        # Nível 1
        if any(term in clean_text for term in ["nível 1", "nivel 1", "nivel1", "nível1"]) or \
           re.search(r"(?:f\d+|_|\b)p1(?:_|\.|\b)", clean_text):
            return "p1"

        # Nível 2
        if any(term in clean_text for term in ["nível 2", "nivel 2", "nivel2", "nível2"]) or \
           re.search(r"(?:f\d+|_|\b)p2(?:_|\.|\b)", clean_text):
            return "p2"

        # Sênior / Universitário
        if any(term in clean_text for term in ["sênior", "senior", "nível sênior", "nivel senior"]) or \
           re.search(r"(?:f\d+|_|\b)(?:ps|pu)(?:_|\.|\b)", clean_text):
            return "senior"

        # Fallback para fases
        fase_match = re.search(r"fase\s*(\d+[ab]?)", clean_text)
        if fase_match:
            return f"fase{fase_match.group(1)}"

        return "geral"

    def infer_language(self, filename: str) -> Optional[str]:
        """Infers the programming language from filename extension."""
        suffix = Path(filename).suffix.lower()
        # Tratamento para extensoes duplas ou especiais (ex: .c.txt -> .c ou .py3 -> py)
        if filename.lower().endswith(".py3"):
            return "py"
        return MAPEAMENTO_LINGUAGEM.get(suffix)

    def infer_problem_name(self, url_path: str) -> str:
        """Infers problem name from solution directory structure or filename."""
        clean_path = url_path.strip("/").replace("\\", "/")
        parts = clean_path.split("/")

        if len(parts) >= 2:
            parent_folder = parts[-2]
            if "_" in parent_folder:
                # Exemplo: 2022f1pj_cinema -> cinema
                return parent_folder.split("_", 1)[1].lower()
            if parent_folder.lower() not in ["solucoes", "codigo", "extras"]:
                return parent_folder.lower()

        # Fallback para nome do arquivo sem extensao
        filename = parts[-1]
        stem = Path(filename).stem
        if "_" in stem:
            return stem.split("_", 1)[0].lower()
        return stem.lower()

    def extract_pdf_links(self, html: str, page_url: str, ano: int) -> list[CadernoLink]:
        """Parses HTML content, extracts all PDF links, resolves absolute URLs and infers levels."""
        soup = BeautifulSoup(html, "html.parser")
        discovered: list[CadernoLink] = []
        seen_urls: set[str] = set()

        for a_tag in soup.find_all("a", href=True):
            href = a_tag["href"].strip()
            if not href.lower().endswith(".pdf"):
                continue

            absolute_url = urljoin(page_url, href)
            if absolute_url in seen_urls:
                continue

            seen_urls.add(absolute_url)
            filename = href.split("/")[-1]
            link_text = a_tag.get_text(strip=True)
            nivel = self.infer_level_or_phase(page_url, link_text, filename)

            discovered.append(CadernoLink(
                url=absolute_url,
                nome_arquivo=filename,
                ano=ano,
                nivel=nivel,
                texto_link=link_text
            ))

        return discovered

    def extract_code_links(self, html: str, page_url: str, ano: int) -> list[CodigoSolucao]:
        """Parses HTML content, extracts official code solution links, resolves absolute URLs."""
        soup = BeautifulSoup(html, "html.parser")
        discovered: list[CodigoSolucao] = []
        seen_urls: set[str] = set()

        for a_tag in soup.find_all("a", href=True):
            href = a_tag["href"].strip()
            lower_href = href.lower()

            # Descartar cadernos PDF
            if lower_href.endswith(".pdf"):
                continue

            # Descartar arquivos de gabarito ou testes
            if "/gabaritos/" in lower_href or "gabarito" in lower_href:
                continue

            # Para arquivos zip, incluir apenas se estiver em pasta de solucoes ou tiver solucao no nome
            if lower_href.endswith(".zip") and "/solucoes/" not in lower_href and "soluc" not in lower_href:
                continue

            # Verificar se extensao eh valida
            has_valid_ext = any(lower_href.endswith(ext) for ext in EXTENSOES_CODIGO)
            if not has_valid_ext:
                continue

            absolute_url = urljoin(page_url, href)

            # Restringir apenas a links do dominio da OBI ou relativos
            if "olimpiada.ic.unicamp.br" not in absolute_url:
                continue

            if absolute_url in seen_urls:
                continue

            filename = href.split("/")[-1]
            linguagem = self.infer_language(filename)
            if not linguagem:
                continue

            seen_urls.add(absolute_url)
            link_text = a_tag.get_text(strip=True)

            # Inferir nivel considerando a URL da pagina e o caminho do proprio link
            nivel = self.infer_level_or_phase(f"{page_url} {href}", link_text, filename)
            nome_problema = self.infer_problem_name(href)

            discovered.append(CodigoSolucao(
                ano=ano,
                nivel=nivel,
                nome_problema=nome_problema,
                linguagem=linguagem,
                url=absolute_url,
                nome_arquivo=filename,
                texto_link=link_text
            ))

        return discovered

    def extract_gabarito_links(self, html: str, page_url: str, ano: int) -> list[GabaritoZIP]:
        """Parses HTML content, extracts test cases and gabarito .zip links, resolving absolute URLs."""
        soup = BeautifulSoup(html, "html.parser")
        discovered: list[GabaritoZIP] = []
        seen_urls: set[str] = set()

        for a_tag in soup.find_all("a", href=True):
            href = a_tag["href"].strip()
            lower_href = href.lower()

            # Descartar links que nao terminam com .zip
            if not lower_href.endswith(".zip"):
                continue

            link_text = a_tag.get_text(strip=True)
            lower_text = link_text.lower()

            # R1: Link deve conter termos de gabarito ou testes no texto visivel ou na URL
            has_term = any(term in lower_href or term in lower_text for term in TERMOS_GABARITO)
            if not has_term:
                continue

            absolute_url = urljoin(page_url, href)

            # Restringir a links do dominio da OBI ou relativos
            if "olimpiada.ic.unicamp.br" not in absolute_url:
                continue

            if absolute_url in seen_urls:
                continue

            seen_urls.add(absolute_url)
            filename = href.split("/")[-1]

            # R2: Se possuir texto visivel nao vazio -> utilizar texto; senao extrair nome do arquivo
            if link_text:
                nome_questao = link_text
            else:
                nome_questao = Path(filename).stem

            nivel = self.infer_level_or_phase(f"{page_url} {href}", link_text, filename)

            discovered.append(GabaritoZIP(
                ano=ano,
                nivel=nivel,
                nome_questao=nome_questao,
                url=absolute_url,
                texto_link=link_text
            ))

        return discovered

