"""Unit tests for GabaritosDownloader."""
import io
import json
import zipfile
from pathlib import Path
from unittest.mock import MagicMock
import pytest
from src.core.http_client import HttpClient
from src.crawler.gabaritos_downloader import GabaritosDownloader
from src.crawler.scraper import GabaritoZIP


def create_valid_zip_bytes() -> bytes:
    """Helper creating a minimal valid in-memory zip file."""
    buf = io.BytesIO()
    with zipfile.ZipFile(buf, "w", zipfile.ZIP_DEFLATED) as zf:
        zf.writestr("test1.in", "42\n")
        zf.writestr("test1.out", "42\n")
    return buf.getvalue()


@pytest.fixture
def mock_http():
    http = MagicMock(spec=HttpClient)
    http.download_file.return_value = True
    return http


@pytest.fixture
def downloader(tmp_path, mock_http):
    return GabaritosDownloader(
        http_client=mock_http,
        base_output_dir=tmp_path / "gabaritos",
        request_delay=0.0
    )


def test_sanitize_filename():
    assert GabaritosDownloader.sanitize_filename('Questao: 1 / 2 * 3? "Teste" <A> | B') == "Questao 1  2  3 Teste A  B"
    assert GabaritosDownloader.sanitize_filename("Entrevistas de Emprego?") == "Entrevistas de Emprego"
    assert GabaritosDownloader.sanitize_filename("normal_name") == "normal_name"


def test_resolve_destination_path(downloader):
    link = GabaritoZIP(
        ano=2023,
        nivel="pj",
        nome_questao="Entrevistas de Emprego?",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2023/gabaritos/2023f1pj_entrevistas.zip"
    )
    dest_path, already_downloaded = downloader.resolve_destination_path(link)

    assert not already_downloaded
    assert dest_path.name == "Entrevistas de Emprego.zip"
    assert dest_path.parent == downloader.base_output_dir / "2023" / "pj"


def test_resolve_destination_path_avoids_double_zip_extension(downloader):
    link = GabaritoZIP(
        ano=2023,
        nivel="pj",
        nome_questao="entrevistas.zip",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2023/gabaritos/2023f1pj_entrevistas.zip"
    )
    dest_path, already_downloaded = downloader.resolve_destination_path(link)

    assert dest_path.name == "entrevistas.zip"


def test_download_gabarito_success_and_manifest(downloader, mock_http):
    link = GabaritoZIP(
        ano=2023,
        nivel="pj",
        nome_questao="Entrevistas de Emprego",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2023/gabaritos/2023f1pj_entrevistas.zip"
    )

    def fake_download(url, dest):
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(create_valid_zip_bytes())
        return True

    mock_http.download_file.side_effect = fake_download

    success, path = downloader.download_gabarito(link)
    assert success
    assert path is not None
    assert path.exists()
    assert zipfile.is_zipfile(path)

    # Verifica se persistiu no manifest
    assert downloader.manifest_path.exists()
    with open(downloader.manifest_path, "r", encoding="utf-8") as f:
        manifest = json.load(f)

    assert link.url in manifest
    assert manifest[link.url] == str(path.relative_to(downloader.base_output_dir))


def test_download_gabarito_idempotent_skip(downloader, mock_http):
    link = GabaritoZIP(
        ano=2023,
        nivel="pj",
        nome_questao="Entrevistas de Emprego",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2023/gabaritos/2023f1pj_entrevistas.zip"
    )

    def fake_download(url, dest):
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(create_valid_zip_bytes())
        return True

    mock_http.download_file.side_effect = fake_download

    # Primeiro download
    success, path = downloader.download_gabarito(link)
    assert success
    assert mock_http.download_file.call_count == 1

    # Segundo download com mesma URL: deve pular requisicao de rede
    success2, path2 = downloader.download_gabarito(link)
    assert success2
    assert path2 == path
    assert mock_http.download_file.call_count == 1


def test_download_gabarito_corrupted_zip_cleanup(downloader, mock_http):
    link = GabaritoZIP(
        ano=2023,
        nivel="pj",
        nome_questao="Entrevistas de Emprego",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2023/gabaritos/corrupt.zip"
    )

    def fake_corrupt_download(url, dest):
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(b"NOT A VALID ZIP CONTENT")
        return True

    mock_http.download_file.side_effect = fake_corrupt_download

    success, path = downloader.download_gabarito(link)
    assert not success
    assert path is None

    # Destino final nao deve conter arquivo corrompido
    expected_path = downloader.base_output_dir / "2023" / "pj" / "Entrevistas de Emprego.zip"
    assert not expected_path.exists()
    assert not downloader.manifest_path.exists()


def test_download_gabarito_force_redownload(downloader, mock_http):
    link = GabaritoZIP(
        ano=2023,
        nivel="pj",
        nome_questao="Entrevistas de Emprego",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2023/gabaritos/2023f1pj_entrevistas.zip"
    )

    def fake_download(url, dest):
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(create_valid_zip_bytes())
        return True

    mock_http.download_file.side_effect = fake_download

    # Primeiro download normal
    downloader.download_gabarito(link)
    assert mock_http.download_file.call_count == 1

    # Download forcado com force=True
    success, path = downloader.download_gabarito(link, force=True)
    assert success
    assert mock_http.download_file.call_count == 2


def test_crawl_and_download_with_filters(downloader, mock_http):
    downloader.scraper.extract_gabarito_links = MagicMock(return_value=[
        GabaritoZIP(ano=2023, nivel="pj", nome_questao="Q1", url="https://u1"),
        GabaritoZIP(ano=2023, nivel="p1", nome_questao="Q2", url="https://u2"),
    ])

    def fake_download(url, dest):
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(create_valid_zip_bytes())
        return True

    mock_http.download_file.side_effect = fake_download
    mock_resp = MagicMock()
    mock_resp.status_code = 200
    mock_resp.text = "<html></html>"
    downloader.http.get.return_value = mock_resp

    stats = downloader.crawl_and_download(
        ano_filtro=2023,
        nivel_filtro="pj"
    )

    assert stats["encontrados"] == 1
    assert stats["baixados"] == 1
    assert stats["falhas"] == 0
