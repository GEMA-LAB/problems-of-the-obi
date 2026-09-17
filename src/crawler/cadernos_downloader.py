"""Downloader for OBI exam booklet PDFs with collision resolution and idempotency."""
import json
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
    """Orchestrator for discovering and downloading OBI exam booklets with R6 collision numbering."""

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
        self.manifest_path = self.base_output_dir / ".manifest.json"
        self._manifest: dict[str, str] = self._load_manifest()

    def _load_manifest(self) -> dict[str, str]:
        """Loads the download URL-to-path manifest."""
        if self.manifest_path.exists():
            try:
                with open(self.manifest_path, "r", encoding="utf-8") as f:
                    return json.load(f)
            except (json.JSONDecodeError, OSError):
                return {}
        return {}

    def _save_manifest(self) -> None:
        """Persists the manifest file."""
        try:
            self.base_output_dir.mkdir(parents=True, exist_ok=True)
            with open(self.manifest_path, "w", encoding="utf-8") as f:
                json.dump(self._manifest, f, indent=2, ensure_ascii=False)
        except OSError:
            pass

    def get_destination_path(self, link: CadernoLink) -> Path:
        """Returns standard destination path: base/ano/nivel/nome_arquivo."""
        return self.base_output_dir / str(link.ano) / link.nivel / link.nome_arquivo

    def resolve_destination_path(self, link: CadernoLink, force: bool = False) -> tuple[Path, bool]:
        """
        Resolves destination path for link enforcing rule R6.
        Returns:
            (target_path, already_downloaded_for_this_url)
        """
        # 1. Se a URL ja estiver no manifest e o arquivo existir em disco
        if link.url in self._manifest and not force:
            rel_path = self._manifest[link.url]
            existing_path = self.base_output_dir / rel_path
            if existing_path.exists():
                return existing_path, True

        base_folder = self.base_output_dir / str(link.ano) / link.nivel
        stem = Path(link.nome_arquivo).stem
        suffix = Path(link.nome_arquivo).suffix
        target_path = base_folder / link.nome_arquivo

        # 2. Se o arquivo base nao existir, este e o destino
        if not target_path.exists() or force:
            return target_path, False

        # 3. Se target_path ja existe, verificar se ja pertence a outra URL
        rel_str = str(target_path.relative_to(self.base_output_dir))
        url_owner = None
        for u, path_str in self._manifest.items():
            if path_str == rel_str:
                url_owner = u
                break

        # Se ninguem reivindicou este arquivo no manifest, podemos atribuir a esta URL
        if url_owner is None:
            self._manifest[link.url] = rel_str
            self._save_manifest()
            return target_path, True

        # Se ja pertence a outra URL (ex: Fase 1 x Fase 1B), aplicar R6: [nome]-[numero].pdf
        counter = 1
        while True:
            candidate_name = f"{stem}-{counter}{suffix}"
            candidate_path = base_folder / candidate_name
            candidate_rel = str(candidate_path.relative_to(self.base_output_dir))

            if not candidate_path.exists():
                return candidate_path, False

            # Se o arquivo candidato existe, verificar se ja pertence a esta URL
            if self._manifest.get(link.url) == candidate_rel:
                return candidate_path, True

            counter += 1

    def download_caderno(self, link: CadernoLink, force: bool = False) -> tuple[bool, Path]:
        """Downloads a single booklet PDF with idempotency and R6 collision numbering."""
        target_path, already_downloaded = self.resolve_destination_path(link, force=force)

        if already_downloaded and not force:
            return True, target_path

        success = self.http.download_file(link.url, target_path)

        # Fallback para URLs quebradas com erro de digitação no portal da Unicamp (ex: pu vs ps)
        if not success:
            for old_pat, new_pat in [("pu.pdf", "ps.pdf"), ("ps.pdf", "pu.pdf")]:
                if old_pat in link.url:
                    alt_url = link.url.replace(old_pat, new_pat)
                    alt_path = target_path.with_name(target_path.name.replace(old_pat, new_pat))
                    if self.http.download_file(alt_url, alt_path):
                        success = True
                        target_path = alt_path
                        break

        if success:
            rel_path = str(target_path.relative_to(self.base_output_dir))
            self._manifest[link.url] = rel_path
            self._save_manifest()

            if self.request_delay > 0:
                time.sleep(self.request_delay)

        return success, target_path

    def probe_static_cadernos(self, ano: int) -> list[CadernoLink]:
        """Probes known static asset paths for unindexed or 404 competition years."""
        discovered: list[CadernoLink] = []
        phases = ["f1", "f2", "f3"]
        levels = ["pj", "p1", "p2", "ps", "pu"]

        for phase in phases:
            for level in levels:
                filename = f"ProvaOBI{ano}_{phase}{level}.pdf"
                url = f"https://olimpiada.ic.unicamp.br/static/extras/obi{ano}/provas/{filename}"
                response = self.http.head(url)
                if response is not None and response.status_code == 200:
                    inferred_level = self.scraper.infer_level_or_phase("", "", filename)
                    discovered.append(CadernoLink(
                        url=url,
                        nome_arquivo=filename,
                        ano=ano,
                        nivel=inferred_level,
                        texto_link=f"Caderno {inferred_level.upper()} {phase.upper()}"
                    ))

        return discovered

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
            ano_links: list[CadernoLink] = []

            for padrao in padroes_url:
                page_url = f"{BASE_OBI_URL}OBI{ano}/{padrao}"
                response = self.http.get(page_url)

                if response is None or response.status_code != 200:
                    continue

                links = self.scraper.extract_pdf_links(response.text, page_url, ano)
                ano_links.extend(links)

            # Fallback para probing estatico se a edicao nao possuir paginas ativas no portal (ex: 2018, 2026)
            if not ano_links:
                static_links = self.probe_static_cadernos(ano)
                ano_links.extend(static_links)

            for link in ano_links:
                if link.url in urls_visitadas:
                    continue

                if nivel_filtro and link.nivel.lower() != nivel_filtro.lower():
                    continue

                urls_visitadas.add(link.url)
                stats["encontrados"] += 1

                target_path, already_downloaded = self.resolve_destination_path(link, force=force)
                if already_downloaded and not force:
                    stats["ja_existentes"] += 1
                    continue

                success, _ = self.download_caderno(link, force=force)
                if success:
                    stats["baixados"] += 1
                else:
                    stats["falhas"] += 1

        return stats
