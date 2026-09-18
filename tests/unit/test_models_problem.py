"""Tests for ProblemSchema, Exemplo and ExtractorConfig models."""
from dataclasses import asdict, is_dataclass
from pathlib import Path
import pytest
from src.core.config import ExtractorConfig, DEFAULT_OUTPUT_DIR, DEFAULT_CADERNOS_DIR
from src.models.problem import Exemplo, ProblemSchema


def test_exemplo_instantiation():
    """Validates instantiation of Exemplo."""
    ex = Exemplo(input="4\n1 2 3 4", output="10")
    assert ex.input == "4\n1 2 3 4"
    assert ex.output == "10"
    assert asdict(ex) == {"input": "4\n1 2 3 4", "output": "10"}


def test_problem_schema_instantiation():
    """Validates complete ProblemSchema instantiation with Python limits and without difficulty."""
    examples = [Exemplo(input="1 2", output="3")]
    problem = ProblemSchema(
        title="Soma Simples",
        statement="Dado dois inteiros A e B, calcule a soma.",
        input="Dois inteiros na mesma linha.",
        output="Imprima a soma.",
        constraints="1 <= A, B <= 1000",
        examples=examples,
        imgs=[],
        rating=[100],
        year="2024",
        level="PJ",
        period="Fase 1",
        topics=["ad-hoc", "iniciante"],
        time_limit=2.0,
        memory_limit=512,
    )

    assert problem.title == "Soma Simples"
    assert problem.statement.startswith("Dado dois inteiros")
    assert problem.time_limit == 2.0
    assert isinstance(problem.time_limit, float)
    assert problem.memory_limit == 512
    assert isinstance(problem.memory_limit, int)
    assert problem.year == "2024"
    assert problem.level == "PJ"

    # Ensure difficulty is NOT a field in ProblemSchema
    assert not hasattr(problem, "difficulty")
    problem_dict = problem.to_dict()
    assert "difficulty" not in problem_dict
    assert "time_limit" in problem_dict
    assert "memory_limit" in problem_dict
    assert problem_dict["time_limit"] == 2.0
    assert problem_dict["memory_limit"] == 512
    assert len(problem_dict["examples"]) == 1
    assert problem_dict["examples"][0] == {"input": "1 2", "output": "3"}


def test_problem_schema_from_dict():
    """Validates creating ProblemSchema from dictionary (as received from LLM json output)."""
    raw_dict = {
        "title": "Idade de Camila",
        "statement": "Cibele, Camila e Celeste sao tres irmas...",
        "input": "Tres inteiros...",
        "output": "Um inteiro...",
        "constraints": "5 <= idade <= 100",
        "examples": [{"input": "6\n9\n7", "output": "7"}],
        "imgs": [],
        "rating": [100],
        "year": "2021",
        "level": "PJ",
        "period": "Fase 1",
        "topics": ["condicionais"],
        "time_limit": 1.0,
        "memory_limit": 256,
        # Even if legacy/noisy data has difficulty, from_dict must filter or ignore it
        "difficulty": "Facil",
    }

    problem = ProblemSchema.from_dict(raw_dict)
    assert problem.title == "Idade de Camila"
    assert problem.year == "2021"
    assert problem.time_limit == 1.0
    assert problem.memory_limit == 256
    assert len(problem.examples) == 1
    assert isinstance(problem.examples[0], Exemplo)
    assert not hasattr(problem, "difficulty")
    assert "difficulty" not in problem.to_dict()


def test_extractor_config_defaults():
    """Validates default values for ExtractorConfig."""
    config = ExtractorConfig()
    assert config.base_url is None
    assert config.api_key is None
    assert config.model == "gpt-4o-mini"
    assert config.pasta_entrada == DEFAULT_CADERNOS_DIR
    assert config.pasta_output == DEFAULT_OUTPUT_DIR
    assert config.prompt_template_path == Path("src/prompts/extraction_prompt.md")
