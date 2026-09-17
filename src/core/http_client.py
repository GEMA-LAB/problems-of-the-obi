"""HTTP Client with timeout enforcement and streaming download capability."""
import time
import requests
from pathlib import Path
from typing import Optional
from src.core.config import DEFAULT_TIMEOUT


class HttpClient:
    """Robust HTTP client wrapper for crawler operations."""

    def __init__(self, timeout: int = DEFAULT_TIMEOUT):
        self.timeout = timeout
        self.session = requests.Session()
        self.session.headers.update({
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
        })

    def get(self, url: str, stream: bool = False, timeout: Optional[int] = None) -> Optional[requests.Response]:
        """Performs a GET request with timeout and error handling."""
        effective_timeout = timeout if timeout is not None else self.timeout
        try:
            response = self.session.get(url, stream=stream, timeout=effective_timeout)
            return response
        except requests.RequestException:
            return None

    def download_file(self, url: str, destination_path: Path, timeout: Optional[int] = None, chunk_size: int = 8192) -> bool:
        """Downloads a file using streaming and atomic writing to prevent corruption."""
        effective_timeout = timeout if timeout is not None else self.timeout
        try:
            response = self.session.get(url, stream=True, timeout=effective_timeout)
            if response.status_code != 200:
                return False

            destination_path.parent.mkdir(parents=True, exist_ok=True)
            temp_destination = destination_path.with_suffix(f"{destination_path.suffix}.tmp")

            with open(temp_destination, "wb") as f:
                for chunk in response.iter_content(chunk_size=chunk_size):
                    if chunk:
                        f.write(chunk)

            # Move atomically from temp to final destination
            temp_destination.replace(destination_path)
            return True
        except (requests.RequestException, OSError):
            # Clean up temp file if present on failure
            temp_dest = destination_path.with_suffix(f"{destination_path.suffix}.tmp")
            if temp_dest.exists():
                try:
                    temp_dest.unlink()
                except OSError:
                    pass
            return False
