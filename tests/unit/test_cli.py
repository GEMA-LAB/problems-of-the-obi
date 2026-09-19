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


def test_cli_download_codigos_step():
    test_args = ["main.py", "--step", "download-codigos", "--ano", "2022", "--nivel", "p1"]

    with patch.object(sys, "argv", test_args):
        with patch("main.CodigosDownloader") as mock_downloader_cls:
            mock_instance = MagicMock()
            mock_downloader_cls.return_value = mock_instance
            mock_instance.crawl_and_download.return_value = {"encontrados": 2, "baixados": 2, "ja_existentes": 0, "falhas": 0}

            main()

            mock_downloader_cls.assert_called_once()
            mock_instance.crawl_and_download.assert_called_once_with(
                ano_filtro=2022,
                nivel_filtro="p1",
                force=False
            )


def test_cli_download_gabaritos_step():
    test_args = ["main.py", "--step", "download-gabaritos", "--ano", "2023", "--nivel", "senior"]

    with patch.object(sys, "argv", test_args):
        with patch("main.GabaritosDownloader") as mock_downloader_cls:
            mock_instance = MagicMock()
            mock_downloader_cls.return_value = mock_instance
            mock_instance.crawl_and_download.return_value = {"encontrados": 3, "baixados": 3, "ja_existentes": 0, "falhas": 0}

            main()

            mock_downloader_cls.assert_called_once()
            mock_instance.crawl_and_download.assert_called_once_with(
                ano_filtro=2023,
                nivel_filtro="senior",
                force=False
            )


def test_cli_extract_questions_step():
    test_args = ["main.py", "--step", "extract-questions", "--ano", "2024", "--nivel", "pj"]

    with patch.object(sys, "argv", test_args):
        with patch("main.OpenAiExtractor") as mock_extractor_cls:
            mock_instance = MagicMock()
            mock_extractor_cls.return_value = mock_instance
            mock_instance.process_cadernos.return_value = ([], [])

            main()

            mock_extractor_cls.assert_called_once()


def test_cli_organize_questions_step():
    test_args = ["main.py", "--step", "organize-questions", "--ano", "2023", "--nivel", "pj", "--force"]

    with patch.object(sys, "argv", test_args):
        with patch("main.QuestionsOrganizer") as mock_organizer_cls:
            mock_instance = MagicMock()
            mock_organizer_cls.return_value = mock_instance
            mock_instance.organize_all.return_value = {
                "total_encontradas": 1,
                "sucesso": 1,
                "parcial": 0,
                "ignoradas_idempotentes": 0,
                "removidas_sem_testes": 0,
                "total_testes": 2,
                "total_solucoes": 1,
            }

            main()

            mock_organizer_cls.assert_called_once()
            mock_instance.organize_all.assert_called_once()
            call_kwargs = mock_instance.organize_all.call_args.kwargs
            assert call_kwargs["ano_filtro"] == 2023
            assert call_kwargs["nivel_filtro"] == "pj"
            assert call_kwargs["config"].force is True


def test_cli_organize_testcases_alias_step():
    test_args = ["main.py", "--step", "organize-testcases", "--ano", "2022"]

    with patch.object(sys, "argv", test_args):
        with patch("main.QuestionsOrganizer") as mock_organizer_cls:
            mock_instance = MagicMock()
            mock_organizer_cls.return_value = mock_instance
            mock_instance.organize_all.return_value = {"total_encontradas": 0}

            main()

            mock_organizer_cls.assert_called_once()
            call_kwargs = mock_instance.organize_all.call_args.kwargs
            assert call_kwargs["ano_filtro"] == 2022
            assert call_kwargs["config"].force is False


def test_cli_export_python_dataset_step():
    test_args = ["main.py", "--step", "export-python-dataset", "--ano", "2024", "--nivel", "pj", "--force"]

    with patch.object(sys, "argv", test_args):
        with patch("main.PythonDatasetBuilder") as mock_builder_cls:
            mock_instance = MagicMock()
            mock_builder_cls.return_value = mock_instance
            mock_instance.build_dataset.return_value = {
                "total_questoes_analisadas": 10,
                "questoes_com_python": 5,
                "questoes_exportadas": 5,
            }

            main()

            mock_builder_cls.assert_called_once()
            mock_instance.build_dataset.assert_called_once()
            call_kwargs = mock_instance.build_dataset.call_args.kwargs
            assert call_kwargs["ano_filtro"] == 2024
            assert call_kwargs["nivel_filtro"] == "pj"
            assert call_kwargs["force"] is True



