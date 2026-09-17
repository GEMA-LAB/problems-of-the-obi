"""Unit tests for src.crawler.cadernos_downloader."""
import pytest
from pathlib import Path
from unittest.mock import MagicMock
from src.crawler.cadernos_downloader import CadernosDownloader
from src.crawler.scraper import CadernoLink
from src.core.http_client import HttpClient


def test_download_caderno_already_exists(tmp_path):
    mock_http = MagicMock(spec=HttpClient)
    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    link = CadernoLink(
        url="https://example.com/caderno_pj.pdf",
        nome_arquivo="caderno_pj.pdf",
        ano=2024,
        nivel="pj",
        texto_link="Caderno PJ"
    )

    # Cria o arquivo previamente
    expected_path = tmp_path / "2024" / "pj" / "caderno_pj.pdf"
    expected_path.parent.mkdir(parents=True, exist_ok=True)
    expected_path.write_bytes(b"%PDF-1.4 dummy")

    success, path = downloader.download_caderno(link, force=False)

    assert success is True
    assert path == expected_path
    # Não deve chamar download_file pois já existia
    mock_http.download_file.assert_not_called()


def test_download_caderno_new_file_success(tmp_path):
    mock_http = MagicMock(spec=HttpClient)
    mock_http.download_file.return_value = True

    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    link = CadernoLink(
        url="https://example.com/caderno_p1.pdf",
        nome_arquivo="caderno_p1.pdf",
        ano=2023,
        nivel="p1",
        texto_link="Caderno P1"
    )

    expected_path = tmp_path / "2023" / "p1" / "caderno_p1.pdf"

    success, path = downloader.download_caderno(link)

    assert success is True
    assert path == expected_path
    mock_http.download_file.assert_called_once_with(link.url, expected_path)


def test_download_caderno_failure(tmp_path):
    mock_http = MagicMock(spec=HttpClient)
    mock_http.download_file.return_value = False

    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    link = CadernoLink(
        url="https://example.com/fail.pdf",
        nome_arquivo="fail.pdf",
        ano=2022,
        nivel="senior",
        texto_link="Caderno Senior"
    )

    success, path = downloader.download_caderno(link)

    assert success is False


def test_crawl_and_download_with_filter(tmp_path, sample_obi_html):
    mock_http = MagicMock(spec=HttpClient)
    mock_response = MagicMock()
    mock_response.status_code = 200
    mock_response.text = sample_obi_html
    mock_http.get.return_value = mock_response
    mock_http.download_file.return_value = True

    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    # Filtrar apenas nível 'pj'
    stats = downloader.crawl_and_download(
        start_year=2024,
        end_year=2025,
        padroes=["fase1/programacao/cadernos/"],
        nivel_filtro="pj"
    )

    # O sample_obi_html possui 3 cadernos (pj, p1, p2). Filtrando 'pj', apenas 1 deve ser baixado.
    assert stats["encontrados"] == 1
    assert stats["baixados"] == 1
    assert stats["falhas"] == 0
