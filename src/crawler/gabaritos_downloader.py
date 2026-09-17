"""Downloader for OBI official gabarito and test cases ZIP files with idempotency and integrity validation."""
import json
import re
import time
import zipfile
from pathlib import Path
from typing import Optional
from src.core.config import (
    BASE_OBI_URL,
    DEFAULT_GABARITOS_DIR,
    DEFAULT_REQUEST_DELAY,
    PADROES_CADERNOS,
    START_YEAR,
    END_YEAR,
    GabaritoCrawlerConfig,
)
from src.core.http_client import HttpClient
from src.crawler.scraper import ObiScraper, GabaritoZIP


class GabaritosDownloader:
    """Orchestrator for discovering and downloading official OBI test cases and gabaritos (.zip)."""

    def __init__(
        self,
        http_client: Optional[HttpClient] = None,
        base_output_dir: Path = DEFAULT_GABARITOS_DIR,
        request_delay: float = DEFAULT_REQUEST_DELAY,
        config: Optional[GabaritoCrawlerConfig] = None,
    ):
        self.http = http_client or HttpClient()
        self.base_output_dir = Path(base_output_dir)
        self.request_delay = request_delay
        self.config = config or GabaritoCrawlerConfig(
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
        """Removes invalid characters for Windows/Linux file systems (R3, I2)."""
        nome_limpo = re.sub(r'[\\/*?:"<>|]', "", nome)
        return nome_limpo.strip()

    def resolve_destination_path(self, link: GabaritoZIP, force: bool = False) -> tuple[Path, bool]:
        """
        Resolves destination path for link enforcing R2, R3 and R4 (idempotency).
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
        clean_name = self.sanitize_filename(link.nome_questao)

        if not clean_name.lower().endswith(".zip"):
            target_name = f"{clean_name}.zip"
        else:
            target_name = clean_name

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

        # Se esta associado a esta URL ou ainda nao foi registrado
        if url_owner is None or url_owner == link.url:
            self._manifest[link.url] = rel_str
            self._save_manifest()
            return target_path, True

        # Se ja pertence a outra URL distinta, gerar sufixo numerico incremental
        stem = target_path.stem
        counter = 1
        while True:
            candidate_name = f"{stem}-{counter}.zip"
            candidate_path = base_folder / candidate_name
            candidate_rel = str(candidate_path.relative_to(self.base_output_dir))

            if not candidate_path.exists():
                return candidate_path, False

            candidate_owner = None
            for u, path_str in self._manifest.items():
                if path_str == candidate_rel:
                    candidate_owner = u
                    break

            if candidate_owner == link.url:
                return candidate_path, True

            counter += 1

    def validate_zip(self, path: Path) -> bool:
        """Validates if file is an intact, non-empty ZIP archive (Invariante I1, R5)."""
        if not path.exists() or path.stat().st_size == 0:
            return False
        if not zipfile.is_zipfile(path):
            return False
        try:
            with zipfile.ZipFile(path, "r") as zf:
                return zf.testzip() is None
        except Exception:
            return False

    def download_gabarito(self, link: GabaritoZIP, force: bool = False) -> tuple[bool, Optional[Path]]:
        """
        Downloads a test cases ZIP archive with idempotency, temporary buffering,
        and strict zip integrity validation.
        """
        target_path, already_downloaded = self.resolve_destination_path(link, force=force)

        if already_downloaded and not force:
            return True, target_path

        target_path.parent.mkdir(parents=True, exist_ok=True)
        temp_path = target_path.with_name(f"{target_path.stem}.tmp")

        if temp_path.exists():
            try:
                temp_path.unlink()
            except OSError:
                pass

        success = self.http.download_file(link.url, temp_path)

        if not success or not self.validate_zip(temp_path):
            # Excluir residuo se falhou ou esta corrompido (R5, I1)
            if temp_path.exists():
                try:
                    temp_path.unlink()
                except OSError:
                    pass
            return False, None

        # Substituir arquivo atomico
        try:
            temp_path.replace(target_path)
        except OSError:
            import shutil
            shutil.move(str(temp_path), str(target_path))

        rel_str = str(target_path.relative_to(self.base_output_dir))
        self._manifest[link.url] = rel_str
        self._save_manifest()

        return True, target_path

    def crawl_and_download(
        self,
        ano_filtro: Optional[int] = None,
        nivel_filtro: Optional[str] = None,
        force: bool = False,
    ) -> dict[str, int]:
        """
        Orchestrates crawling and downloading official OBI test case ZIPs.
        """
        stats = {
            "encontrados": 0,
            "baixados": 0,
            "ja_existentes": 0,
            "falhas": 0,
        }

        anos = [ano_filtro] if ano_filtro else list(range(START_YEAR, END_YEAR))
        seen_urls: set[str] = set()

        for ano in anos:
            print(f"\nBuscando gabaritos do ano: {ano}")

            for padrao in PADROES_CADERNOS:
                page_url = f"{BASE_OBI_URL}OBI{ano}/{padrao}"
                try:
                    resp = self.http.get(page_url)
                    if not resp or resp.status_code != 200:
                        continue

                    links = self.scraper.extract_gabarito_links(resp.text, page_url, ano)

                    for link in links:
                        if nivel_filtro and link.nivel.lower() != nivel_filtro.lower():
                            continue

                        if link.url in seen_urls:
                            continue

                        seen_urls.add(link.url)
                        stats["encontrados"] += 1

                        dest, already = self.resolve_destination_path(link, force=force)
                        if already and not force:
                            stats["ja_existentes"] += 1
                            print(f"  -> Ja presente: {dest.name}")
                            continue

                        print(f"  -> Baixando gabarito: {link.nome_questao} ...", end=" ", flush=True)
                        ok, path = self.download_gabarito(link, force=force)

                        if ok:
                            stats["baixados"] += 1
                            print("OK")
                        else:
                            stats["falhas"] += 1
                            print("FALHA")

                        if self.request_delay > 0:
                            time.sleep(self.request_delay)

                except Exception as e:
                    print(f"Erro ao acessar {page_url}: {e}")
                    continue

        return stats
