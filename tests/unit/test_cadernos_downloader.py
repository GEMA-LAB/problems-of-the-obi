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

    # Cria o arquivo previamente e cadastra no manifest
    expected_path = tmp_path / "2024" / "pj" / "caderno_pj.pdf"
    expected_path.parent.mkdir(parents=True, exist_ok=True)
    expected_path.write_bytes(b"%PDF-1.4 dummy")
    downloader._manifest[link.url] = str(expected_path.relative_to(tmp_path))
    downloader._save_manifest()

    success, path = downloader.download_caderno(link, force=False)

    assert success is True
    assert path == expected_path
    # Não deve chamar download_file pois já existia para essa mesma URL
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


def test_download_caderno_collision_creates_numbered_suffix(tmp_path):
    """Regra R6: Se o arquivo já existir para outra URL, salva como [nome]-[numero].pdf."""
    mock_http = MagicMock(spec=HttpClient)
    mock_http.download_file.return_value = True

    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    # 1º Link (Fase 1 normal)
    link1 = CadernoLink(
        url="https://example.com/fase1/caderno_pj.pdf",
        nome_arquivo="caderno_pj.pdf",
        ano=2021,
        nivel="pj",
        texto_link="Caderno Fase 1"
    )
    success1, path1 = downloader.download_caderno(link1)
    assert success1 is True
    assert path1 == tmp_path / "2021" / "pj" / "caderno_pj.pdf"
    # Simula a escrita real do arquivo
    path1.parent.mkdir(parents=True, exist_ok=True)
    path1.write_bytes(b"%PDF-1.4 dummy 1")

    # 2º Link (Fase 1B com mesmo nome de arquivo)
    link2 = CadernoLink(
        url="https://example.com/fase1b/caderno_pj.pdf",
        nome_arquivo="caderno_pj.pdf",
        ano=2021,
        nivel="pj",
        texto_link="Caderno Fase 1B"
    )
    success2, path2 = downloader.download_caderno(link2)
    assert success2 is True
    assert path2 == tmp_path / "2021" / "pj" / "caderno_pj-1.pdf"
    path2.write_bytes(b"%PDF-1.4 dummy 2")

    # 3º Link (Fase 1C ou outra prova com mesmo nome)
    link3 = CadernoLink(
        url="https://example.com/fase1c/caderno_pj.pdf",
        nome_arquivo="caderno_pj.pdf",
        ano=2021,
        nivel="pj",
        texto_link="Caderno Fase 1C"
    )
    success3, path3 = downloader.download_caderno(link3)
    assert success3 is True
    assert path3 == tmp_path / "2021" / "pj" / "caderno_pj-2.pdf"


def test_download_caderno_collision_idempotency_preserves_numbered_files(tmp_path):
    """Reexecuções de URLs já mapeadas não geram novos números."""
    mock_http = MagicMock(spec=HttpClient)
    mock_http.download_file.return_value = True

    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    link1 = CadernoLink(
        url="https://example.com/fase1/caderno_pj.pdf",
        nome_arquivo="caderno_pj.pdf",
        ano=2021,
        nivel="pj",
        texto_link="Caderno Fase 1"
    )
    link2 = CadernoLink(
        url="https://example.com/fase1b/caderno_pj.pdf",
        nome_arquivo="caderno_pj.pdf",
        ano=2021,
        nivel="pj",
        texto_link="Caderno Fase 1B"
    )

    # 1ª execução
    downloader.download_caderno(link1)
    (tmp_path / "2021" / "pj" / "caderno_pj.pdf").parent.mkdir(parents=True, exist_ok=True)
    (tmp_path / "2021" / "pj" / "caderno_pj.pdf").write_bytes(b"content 1")

    downloader.download_caderno(link2)
    (tmp_path / "2021" / "pj" / "caderno_pj-1.pdf").write_bytes(b"content 2")

    mock_http.download_file.reset_mock()

    # 2ª execução (mesmas URLs)
    s1, p1 = downloader.download_caderno(link1)
    s2, p2 = downloader.download_caderno(link2)

    assert s1 is True
    assert p1 == tmp_path / "2021" / "pj" / "caderno_pj.pdf"
    assert s2 is True
    assert p2 == tmp_path / "2021" / "pj" / "caderno_pj-1.pdf"
    # Nenhuma chamada de download_file pois ambos já existem e estão mapeados
    mock_http.download_file.assert_not_called()


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


def test_probe_static_cadernos_finds_candidates(tmp_path):
    mock_http = MagicMock(spec=HttpClient)
    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    # Simula que ProvaOBI2018_f1pj.pdf e ProvaOBI2018_f1p1.pdf existem via HEAD
    def mock_head(url):
        res = MagicMock()
        if "ProvaOBI2018_f1pj.pdf" in url or "ProvaOBI2018_f1p1.pdf" in url:
            res.status_code = 200
            return res
        res.status_code = 404
        return res

    mock_http.head.side_effect = mock_head

    links = downloader.probe_static_cadernos(2018)

    assert len(links) == 2
    filenames = [l.nome_arquivo for l in links]
    assert "ProvaOBI2018_f1pj.pdf" in filenames
    assert "ProvaOBI2018_f1p1.pdf" in filenames
    levels = {l.nome_arquivo: l.nivel for l in links}
    assert levels["ProvaOBI2018_f1pj.pdf"] == "pj"
    assert levels["ProvaOBI2018_f1p1.pdf"] == "p1"


def test_crawl_and_download_triggers_static_probing_when_no_html_links_found(tmp_path):
    mock_http = MagicMock(spec=HttpClient)
    # Pagina HTML retorna 404
    mock_http.get.return_value = None
    mock_http.download_file.return_value = True

    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    # Mock de probe_static_cadernos
    link_2018 = CadernoLink(
        url="https://olimpiada.ic.unicamp.br/static/extras/obi2018/provas/ProvaOBI2018_f1pj.pdf",
        nome_arquivo="ProvaOBI2018_f1pj.pdf",
        ano=2018,
        nivel="pj",
        texto_link="Caderno PJ"
    )
    downloader.probe_static_cadernos = MagicMock(return_value=[link_2018])

    stats = downloader.crawl_and_download(ano_filtro=2018)

    downloader.probe_static_cadernos.assert_called_once_with(2018)
    assert stats["encontrados"] == 1
    assert stats["baixados"] == 1
    assert stats["falhas"] == 0


def test_crawl_and_download_processes_cfobi(tmp_path):
    mock_http = MagicMock(spec=HttpClient)
    mock_response = MagicMock()
    mock_response.status_code = 200
    mock_response.text = '''
    <html>
        <body>
            <a href="/static/extras/obi2024/provas/ProvaOBI2024_cfpj.pdf">Caderno Feminina PJ</a>
        </body>
    </html>
    '''
    mock_http.get.return_value = mock_response
    mock_http.download_file.return_value = True

    downloader = CadernosDownloader(http_client=mock_http, base_output_dir=tmp_path, request_delay=0)

    stats = downloader.crawl_and_download(
        ano_filtro=2024,
        padroes=["cfobi/programacao/cadernos/"]
    )

    assert stats["encontrados"] == 1
    assert stats["baixados"] == 1
    expected_path = tmp_path / "2024" / "pj" / "ProvaOBI2024_cfpj.pdf"
    mock_http.download_file.assert_called_once_with(
        "https://olimpiada.ic.unicamp.br/static/extras/obi2024/provas/ProvaOBI2024_cfpj.pdf",
        expected_path
    )
