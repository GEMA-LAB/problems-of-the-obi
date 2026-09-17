"""HTML parser and link extractor for OBI past exams."""
import re
from dataclasses import dataclass
from pathlib import Path
from typing import Optional
from urllib.parse import urljoin
from bs4 import BeautifulSoup



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


class ObiScraper:
    """Scraper for OBI past competition pages."""

    def infer_level_or_phase(self, url_path: str, link_text: str, filename: str) -> str:
        """Infers the competition level (e.g., pj, p1, p2, senior) or phase from metadata."""
        combined_text = f"{url_path} {link_text} {filename}".lower()

        # Checagem de níveis específicos
        if any(term in combined_text for term in ["júnior", "junior", "pj"]):
            return "pj"
        if any(term in combined_text for term in ["nível 1", "nivel 1", "nivel1", "_p1", "p1."]):
            return "p1"
        if any(term in combined_text for term in ["nível 2", "nivel 2", "nivel2", "_p2", "p2."]):
            return "p2"
        if any(term in combined_text for term in ["sênior", "senior", "ps", "pu.", "_pu", "pu-", "_ps", "ps."]):
            return "senior"

        # Fallback para fases
        fase_match = re.search(r"fase\s*(\d+[ab]?)", combined_text)
        if fase_match:
            return f"fase{fase_match.group(1)}"

        return "geral"

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
