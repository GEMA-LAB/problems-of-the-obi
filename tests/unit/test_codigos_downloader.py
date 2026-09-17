"""Unit tests for CodigosDownloader."""
import json
from pathlib import Path
from unittest.mock import MagicMock
import pytest
from src.core.http_client import HttpClient
from src.crawler.codigos_downloader import CodigosDownloader
from src.crawler.scraper import CodigoSolucao


@pytest.fixture
def mock_http():
    http = MagicMock(spec=HttpClient)
    http.download_file.return_value = True
    return http


@pytest.fixture
def downloader(tmp_path, mock_http):
    return CodigosDownloader(
        http_client=mock_http,
        base_output_dir=tmp_path / "codigo",
        request_delay=0.0
    )


def test_resolve_destination_path_prefixes_problem_for_generic_filename(downloader):
    link = CodigoSolucao(
        ano=2022,
        nivel="pj",
        nome_problema="cinema",
        linguagem="cpp",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2022/solucoes/2022f1pj_cinema/andre.cpp",
        nome_arquivo="andre.cpp"
    )
    dest_path, already_done = downloader.resolve_destination_path(link)

    assert not already_done
    assert dest_path.name == "cinema_andre.cpp"
    assert dest_path.parent == downloader.base_output_dir / "2022" / "pj"


def test_resolve_destination_path_preserves_filename_containing_problem_name(downloader):
    link = CodigoSolucao(
        ano=2022,
        nivel="pj",
        nome_problema="cinema",
        linguagem="java",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2022/solucoes/2022f1pj_cinema/cinema.java",
        nome_arquivo="cinema.java"
    )
    dest_path, already_done = downloader.resolve_destination_path(link)

    assert not already_done
    assert dest_path.name == "cinema.java"


def test_download_codigo_success_and_manifest_persistence(downloader, mock_http):
    link = CodigoSolucao(
        ano=2022,
        nivel="pj",
        nome_problema="cinema",
        linguagem="py",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2022/solucoes/2022f1pj_cinema/cinema_py.py",
        nome_arquivo="cinema_py.py"
    )

    def fake_download(url, dest):
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text("print('test')")
        return True

    mock_http.download_file.side_effect = fake_download

    success, path = downloader.download_codigo(link)
    assert success
    assert path.exists()

    # Checar se registrou no manifest
    manifest_file = downloader.manifest_path
    assert manifest_file.exists()
    with open(manifest_file, "r", encoding="utf-8") as f:
        manifest = json.load(f)

    assert link.url in manifest
    assert manifest[link.url] == str(path.relative_to(downloader.base_output_dir))


def test_download_codigo_idempotent_skip(downloader, mock_http):
    link = CodigoSolucao(
        ano=2022,
        nivel="pj",
        nome_problema="cinema",
        linguagem="cpp",
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2022/solucoes/2022f1pj_cinema/andre.cpp",
        nome_arquivo="andre.cpp"
    )

    def fake_download(url, dest):
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text("// test")
        return True

    mock_http.download_file.side_effect = fake_download

    # Primeiro download
    success, path = downloader.download_codigo(link)
    assert success
    assert mock_http.download_file.call_count == 1

    # Segundo download com a mesma URL (deve pular requisicao de rede)
    success2, path2 = downloader.download_codigo(link)
    assert success2
    assert path2 == path
    assert mock_http.download_file.call_count == 1


def test_download_codigo_collision_resolution_different_urls(downloader, mock_http):
    link1 = CodigoSolucao(
        ano=2022,
        nivel="pj",
        nome_problema="cinema",
        linguagem="cpp",
        url="https://olimpiada.ic.unicamp.br/solucoes/cinema/andre.cpp",
        nome_arquivo="andre.cpp"
    )
    link2 = CodigoSolucao(
        ano=2022,
        nivel="pj",
        nome_problema="cinema",
        linguagem="cpp",
        url="https://olimpiada.ic.unicamp.br/solucoes/cinema_b/andre.cpp",
        nome_arquivo="andre.cpp"
    )

    def fake_download(url, dest):
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_text("// code")
        return True

    mock_http.download_file.side_effect = fake_download

    success1, path1 = downloader.download_codigo(link1)
    assert success1
    assert path1.name == "cinema_andre.cpp"

    success2, path2 = downloader.download_codigo(link2)
    assert success2
    assert path2.name == "cinema_andre-1.cpp"


def test_download_codigo_handles_http_failure(downloader, mock_http):
    mock_http.download_file.return_value = False
    link = CodigoSolucao(
        ano=2022,
        nivel="pj",
        nome_problema="cinema",
        linguagem="cpp",
        url="https://olimpiada.ic.unicamp.br/solucoes/error.cpp",
        nome_arquivo="error.cpp"
    )

    success, path = downloader.download_codigo(link)
    assert not success
    assert not downloader.manifest_path.exists()


def test_crawl_and_download_with_filters(downloader, mock_http):
    downloader.scraper.extract_code_links = MagicMock(return_value=[
        CodigoSolucao(ano=2022, nivel="pj", nome_problema="p1", linguagem="cpp", url="https://u1", nome_arquivo="p1.cpp"),
        CodigoSolucao(ano=2022, nivel="p1", nome_problema="p2", linguagem="py", url="https://u2", nome_arquivo="p2.py"),
    ])
    mock_resp = MagicMock()
    mock_resp.status_code = 200
    mock_resp.text = "<html></html>"
    downloader.http.get.return_value = mock_resp

    stats = downloader.crawl_and_download(
        ano_filtro=2022,
        nivel_filtro="pj"
    )

    assert stats["encontrados"] == 1
    assert stats["baixados"] == 1
    assert stats["falhas"] == 0
