"""Tests for OpenAiExtractor including Files API lifecycle, cleanup, and saving."""
import json
from pathlib import Path
from unittest.mock import MagicMock
import pytest
from src.core.config import ExtractorConfig
from src.extractor.openai_extractor import OpenAiExtractor
from src.models.problem import ProblemSchema, Exemplo


@pytest.fixture
def mock_client():
    client = MagicMock()
    mock_file = MagicMock()
    mock_file.id = "file-test-id-123"
    client.files.create.return_value = mock_file
    client.files.delete.return_value = None
    return client


@pytest.fixture
def sample_problem():
    return ProblemSchema(
        title="Torre de Dados",
        statement="Dado um conjunto de dados...",
        input="N inteiros...",
        output="Maior soma...",
        constraints="1 <= N <= 10000",
        examples=[Exemplo(input="3", output="15")],
        year="2024",
        level="PJ",
        period="Fase 1",
        topics=["guloso"],
        time_limit=2.5,
        memory_limit=512,
    )


def test_extract_from_pdf_success(mock_client, tmp_path):
    """Validates successful extraction flow and mandatory files.delete in finally."""
    fake_pdf = tmp_path / "prova.pdf"
    fake_pdf.write_bytes(b"%PDF-1.4 test")

    mock_response = MagicMock()
    mock_response.output_text = """[
        {
            "title": "Torre de Dados",
            "statement": "Dado um conjunto de dados...",
            "input": "N inteiros...",
            "output": "Maior soma...",
            "constraints": "1 <= N <= 10000",
            "examples": [{"input": "3", "output": "15"}],
            "year": "2024",
            "level": "PJ",
            "period": "Fase 1",
            "topics": ["guloso"],
            "time_limit": 2.5,
            "memory_limit": 512
        }
    ]"""
    mock_client.responses.create.return_value = mock_response

    extractor = OpenAiExtractor(client=mock_client)
    problems = extractor.extract_from_pdf(fake_pdf)

    assert len(problems) == 1
    assert problems[0].title == "Torre de Dados"
    assert problems[0].time_limit == 2.5
    assert problems[0].memory_limit == 512

    # Verify Files API usage and deletion
    mock_client.files.create.assert_called_once()
    mock_client.files.delete.assert_called_once_with("file-test-id-123")


def test_extract_from_pdf_always_deletes_remote_file_on_error(mock_client, tmp_path):
    """Validates invariant I1: files.delete is executed even when LLM call throws exception."""
    fake_pdf = tmp_path / "prova_erro.pdf"
    fake_pdf.write_bytes(b"%PDF-1.4 test error")

    mock_client.responses.create.side_effect = RuntimeError("OpenAI rate limit / network error")

    extractor = OpenAiExtractor(client=mock_client)
    with pytest.raises(RuntimeError):
        extractor.extract_from_pdf(fake_pdf)

    # Invariant I1: client.files.delete MUST be called in finally
    mock_client.files.delete.assert_called_once_with("file-test-id-123")


def test_save_problem_standard(sample_problem, tmp_path):
    """Validates saving problem in output_with_code/[ano]/[nivel]/[nome_questao]/problem.json."""
    extractor = OpenAiExtractor(client=MagicMock())
    saved_path = extractor.save_problem(sample_problem, output_base=tmp_path)

    expected_file = tmp_path / "2024" / "pj" / "Torre de Dados" / "problem.json"
    assert saved_path == expected_file
    assert expected_file.exists()

    with open(expected_file, "r", encoding="utf-8") as f:
        data = json.load(f)

    assert data["title"] == "Torre de Dados"
    assert data["time_limit"] == 2.5
    assert data["memory_limit"] == 512
    assert "difficulty" not in data


def test_save_problem_year_and_level_separation(sample_problem, tmp_path):
    """Validates separating problems of same name across different years or levels."""
    extractor = OpenAiExtractor(client=MagicMock())

    # Save problem from 2024 nivel pj
    path_2024 = extractor.save_problem(sample_problem, output_base=tmp_path)
    assert path_2024 == tmp_path / "2024" / "pj" / "Torre de Dados" / "problem.json"
    assert path_2024.exists()

    # Save homonymous problem from 2020 nivel p1
    problem_2020 = ProblemSchema(
        title="Torre de Dados",
        statement="Outro enunciado...",
        input="...",
        output="...",
        constraints="...",
        examples=[],
        year="2020",
        level="P1",
    )
    path_2020 = extractor.save_problem(problem_2020, output_base=tmp_path)
    assert path_2020 == tmp_path / "2020" / "p1" / "Torre de Dados" / "problem.json"
    assert path_2020.exists()
    assert path_2024.exists()


def test_save_problem_sanitizes_special_characters(tmp_path):
    """Validates that question marks '?' in title are cleaned."""
    problem = ProblemSchema(
        title="Qual e o Maior?",
        statement="Descubra o maior.",
        input="a b",
        output="maior",
        constraints="a, b <= 100",
        examples=[],
        year="2022",
    )
    extractor = OpenAiExtractor(client=MagicMock())
    saved_path = extractor.save_problem(problem, output_base=tmp_path)

    expected_dir = tmp_path / "2022" / "geral" / "Qual e o Maior"
    assert saved_path == expected_dir / "problem.json"
    assert expected_dir.exists()


def test_process_cadernos_batch(mock_client, sample_problem, tmp_path):
    """Validates batch processing of booklets returning extracted problems and errors."""
    p1 = tmp_path / "p1.pdf"
    p1.write_bytes(b"%PDF-1")

    mock_response = MagicMock()
    mock_response.output_text = json.dumps([sample_problem.to_dict()])
    mock_client.responses.create.return_value = mock_response

    output_dir = tmp_path / "output_with_code"
    extractor = OpenAiExtractor(client=mock_client)
    extracted, errors = extractor.process_cadernos([p1], output_base=output_dir)

    assert len(extracted) == 1
    assert len(errors) == 0
    assert (output_dir / "2024" / "pj" / "Torre de Dados" / "problem.json").exists()


def test_save_problem_mirrors_cadernos_path(sample_problem, tmp_path):
    """Garante que save_problem utiliza o caminho do PDF em cadernos/ em vez do level da LLM."""
    cadernos_dir = tmp_path / "cadernos"
    pdf_path = cadernos_dir / "2025" / "p1" / "ProvaOBI2025_f1p1.pdf"
    pdf_path.parent.mkdir(parents=True)
    pdf_path.write_bytes(b"%PDF-1.4 test")

    sample_problem.level = "N1"  # LLM retornou N1
    sample_problem.year = "2025"

    output_dir = tmp_path / "output_with_code"
    extractor = OpenAiExtractor(client=MagicMock())

    saved = extractor.save_problem(
        sample_problem,
        output_base=output_dir,
        source_pdf=pdf_path,
        base_cadernos_dir=cadernos_dir,
    )

    expected = output_dir / "2025" / "p1" / "Torre de Dados" / "problem.json"
    assert saved == expected
    assert expected.exists()
    assert not (output_dir / "2025" / "n1").exists()

    with open(saved, "r", encoding="utf-8") as f:
        data = json.load(f)
        assert data["level"] == "p1"


