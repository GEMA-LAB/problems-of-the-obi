"""Unit tests for main.py CLI integration."""
from unittest.mock import patch, MagicMock
from main import main
import sys


def test_cli_download_cadernos_step():
    test_args = ["main.py", "--step", "download-cadernos", "--ano", "2024", "--nivel", "pj"]

    with patch.object(sys, "argv", test_args):
        with patch("main.CadernosDownloader") as mock_downloader_cls:
            mock_instance = MagicMock()
            mock_downloader_cls.return_value = mock_instance
            mock_instance.crawl_and_download.return_value = {"encontrados": 1, "baixados": 1, "ja_existentes": 0, "falhas": 0}

            main()

            mock_downloader_cls.assert_called_once()
            mock_instance.crawl_and_download.assert_called_once_with(
                ano_filtro=2024,
                nivel_filtro="pj",
                force=False
            )
