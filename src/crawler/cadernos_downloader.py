"""Downloader for OBI exam booklet PDFs."""
import time
from pathlib import Path
from typing import Optional
from urllib.parse import urljoin
from src.core.config import (
    BASE_OBI_URL,
    DEFAULT_CADERNOS_DIR,
    DEFAULT_REQUEST_DELAY,
    PADROES_CADERNOS,
    START_YEAR,
    END_YEAR,
)
from src.core.http_client import HttpClient
from src.crawler.scraper import ObiScraper, CadernoLink


class CadernosDownloader:
    """Orchestrator for discovering and downloading OBI exam booklets."""

    def __init__(
        self,
        http_client: Optional[HttpClient] = None,
        base_output_dir: Path = DEFAULT_CADERNOS_DIR,
        request_delay: float = DEFAULT_REQUEST_DELAY,
    ):
        self.http = http_client or HttpClient()
        self.base_output_dir = Path(base_output_dir)
        self.request_delay = request_delay
        self.scraper = ObiScraper()

    def get_destination_path(self, link: CadernoLink) -> Path:
        """Calculates the target file path: base/ano/nivel/nome_arquivo."""
        return self.base_output_dir / str(link.ano) / link.nivel / link.nome_arquivo

    def download_caderno(self, link: CadernoLink, force: bool = False) -> tuple[bool, Path]:
        """Downloads a single booklet PDF with idempotency guarantee."""
        target_path = self.get_destination_path(link)

        if target_path.exists() and not force:
            return True, target_path

        success = self.http.download_file(link.url, target_path)

        if success and self.request_delay > 0:
            time.sleep(self.request_delay)

        return success, target_path

    def crawl_and_download(
        self,
        start_year: int = START_YEAR,
        end_year: int = END_YEAR,
        padroes: Optional[list[str]] = None,
        ano_filtro: Optional[int] = None,
        nivel_filtro: Optional[str] = None,
        force: bool = False,
    ) -> dict[str, int]:
        """Crawls competition years and downloads all matching exam PDFs."""
        padroes_url = padroes or PADROES_CADERNOS
        anos = [ano_filtro] if ano_filtro is not None else range(start_year, end_year)

        stats = {
            "encontrados": 0,
            "baixados": 0,
            "ja_existentes": 0,
            "falhas": 0,
        }
        urls_visitadas: set[str] = set()

        for ano in anos:
            for padrao in padroes_url:
                page_url = f"{BASE_OBI_URL}OBI{ano}/{padrao}"
                response = self.http.get(page_url)

                if response is None or response.status_code != 200:
                    continue

                links = self.scraper.extract_pdf_links(response.text, page_url, ano)

                for link in links:
                    if link.url in urls_visitadas:
                        continue

                    if nivel_filtro and link.nivel.lower() != nivel_filtro.lower():
                        continue

                    urls_visitadas.add(link.url)
                    stats["encontrados"] += 1

                    target_path = self.get_destination_path(link)
                    if target_path.exists() and not force:
                        stats["ja_existentes"] += 1
                        continue

                    success, _ = self.download_caderno(link, force=force)
                    if success:
                        stats["baixados"] += 1
                    else:
                        stats["falhas"] += 1

        return stats
