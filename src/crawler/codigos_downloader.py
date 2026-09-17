"""Downloader for OBI official code solutions with idempotency and author collision resolution."""
import json
import re
import time
from pathlib import Path
from typing import Optional
from src.core.config import (
    BASE_OBI_URL,
    DEFAULT_CODIGO_DIR,
    DEFAULT_REQUEST_DELAY,
    PADROES_CADERNOS,
    START_YEAR,
    END_YEAR,
    CodigoCrawlerConfig,
)
from src.core.http_client import HttpClient
from src.crawler.scraper import ObiScraper, CodigoSolucao


class CodigosDownloader:
    """Orchestrator for discovering and downloading official OBI code solutions."""

    def __init__(
        self,
        http_client: Optional[HttpClient] = None,
        base_output_dir: Path = DEFAULT_CODIGO_DIR,
        request_delay: float = DEFAULT_REQUEST_DELAY,
        config: Optional[CodigoCrawlerConfig] = None,
    ):
        self.http = http_client or HttpClient()
        self.base_output_dir = Path(base_output_dir)
        self.request_delay = request_delay
        self.config = config or CodigoCrawlerConfig(
            pasta_base=self.base_output_dir,
            delay_requests=request_delay
        )
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

    @staticmethod
    def sanitize_filename(nome: str) -> str:
        """Removes invalid characters for Windows/Linux file systems."""
        nome_limpo = re.sub(r'[\\/*?:"<>|]', "", nome)
        return nome_limpo.strip()

    def resolve_destination_path(self, link: CodigoSolucao, force: bool = False) -> tuple[Path, bool]:
        """
        Resolves destination path for link enforcing R2 (idempotency) and R3 (sanitization/collision).
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
        clean_filename = self.sanitize_filename(link.nome_arquivo)

        stem = Path(clean_filename).stem
        suffix = Path(clean_filename).suffix

        # Se o nome do arquivo nao contem o problema, prefixar com o problema para evitar colisoes de autores
        nome_problema = link.nome_problema.lower() if link.nome_problema else ""
        if nome_problema and nome_problema not in stem.lower():
            target_name = f"{nome_problema}_{clean_filename}"
        else:
            target_name = clean_filename

        target_path = base_folder / target_name

        # 2. Se o arquivo nao existe, este e o destino
        if not target_path.exists() or force:
            return target_path, False

        # 3. Se target_path ja existe, verificar se pertence a esta URL no manifest
        rel_str = str(target_path.relative_to(self.base_output_dir))
        url_owner = None
        for u, path_str in self._manifest.items():
            if path_str == rel_str:
                url_owner = u
                break

        if url_owner is None or url_owner == link.url:
            self._manifest[link.url] = rel_str
            self._save_manifest()
            return target_path, True

        # Se pertence a outra URL distinta, gerar sufixo numerado
        counter = 1
        stem_final = Path(target_name).stem
        suffix_final = Path(target_name).suffix
        while True:
            candidate_name = f"{stem_final}-{counter}{suffix_final}"
            candidate_path = base_folder / candidate_name
            candidate_rel = str(candidate_path.relative_to(self.base_output_dir))

            if not candidate_path.exists():
                return candidate_path, False

            if self._manifest.get(link.url) == candidate_rel:
                return candidate_path, True

            counter += 1

    def download_codigo(self, link: CodigoSolucao, force: bool = False) -> tuple[bool, Path]:
        """Downloads a single code file with idempotency and manifest tracking."""
        target_path, already_downloaded = self.resolve_destination_path(link, force=force)

        if already_downloaded and not force:
            return True, target_path

        success = self.http.download_file(link.url, target_path)

        if success:
            rel_path = str(target_path.relative_to(self.base_output_dir))
            self._manifest[link.url] = rel_path
            self._save_manifest()

            if self.request_delay > 0:
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
        """Crawls competition years and downloads all matching official code solutions."""
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
            ano_links: list[CodigoSolucao] = []

            for padrao in padroes_url:
                page_url = f"{BASE_OBI_URL}OBI{ano}/{padrao}"
                response = self.http.get(page_url)

                if response is None or response.status_code != 200:
                    continue

                links = self.scraper.extract_code_links(response.text, page_url, ano)
                ano_links.extend(links)

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

                success, _ = self.download_codigo(link, force=force)
                if success:
                    stats["baixados"] += 1
                else:
                    stats["falhas"] += 1

        return stats
