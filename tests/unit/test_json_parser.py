"""Tests for markdown sanitization and JSON parsing in extractor."""
import json
import pytest
from src.extractor.json_parser import sanitize_json_markdown, parse_problems_json
from src.models.problem import ProblemSchema


def test_sanitize_clean_json():
    """Validates that a clean JSON string is returned trimmed."""
    raw = '  [{"title": "Questao 1"}]  '
    assert sanitize_json_markdown(raw) == '[{"title": "Questao 1"}]'


def test_sanitize_markdown_fenced_json():
    """Validates removing ```json and ``` fences."""
    raw = """```json
[
    {"title": "Questao 1"}
]
```"""
    sanitized = sanitize_json_markdown(raw)
    assert sanitized.startswith("[")
    assert sanitized.endswith("]")
    assert json.loads(sanitized) == [{"title": "Questao 1"}]


def test_sanitize_markdown_without_language():
    """Validates removing generic ``` fences."""
    raw = """```
[{"title": "Questao 2"}]
```"""
    sanitized = sanitize_json_markdown(raw)
    assert sanitized == '[{"title": "Questao 2"}]'


def test_sanitize_json_with_surrounding_text():
    """Validates extracting JSON array when LLM includes commentary before/after."""
    raw = """Segue a resposta no formato solicitado:
[
    {
        "title": "Questao 3"
    }
]
Espero ter ajudado!"""
    sanitized = sanitize_json_markdown(raw)
    assert sanitized.startswith("[")
    assert sanitized.endswith("]")
    assert json.loads(sanitized) == [{"title": "Questao 3"}]


def test_parse_valid_json_array():
    """Validates parsing a standard array of problems into ProblemSchema instances."""
    raw = """[
        {
            "title": "Acelerador de Particulas",
            "statement": "Um acelerador...",
            "input": "Distancia...",
            "output": "Sensor...",
            "constraints": "1 <= D <= 1000",
            "examples": [{"input": "6", "output": "1"}],
            "imgs": [],
            "rating": [100],
            "year": "2020",
            "level": "PJ",
            "period": "Fase 1",
            "topics": ["aritmetica"],
            "time_limit": 1.0,
            "memory_limit": 256
        }
    ]"""

    problems = parse_problems_json(raw)
    assert len(problems) == 1
    p = problems[0]
    assert isinstance(p, ProblemSchema)
    assert p.title == "Acelerador de Particulas"
    assert p.time_limit == 1.0
    assert p.memory_limit == 256
    assert p.year == "2020"
    assert not hasattr(p, "difficulty")


def test_parse_single_object_as_list():
    """Validates that a single JSON object returned by LLM is handled as a list of 1."""
    raw = """{
        "title": "Idade de Camila",
        "statement": "Tres irmas...",
        "input": "Tres inteiros",
        "output": "Idade de Camila",
        "constraints": "5 <= x <= 100",
        "examples": [],
        "year": "2021",
        "time_limit": 2.0,
        "memory_limit": 512
    }"""

    problems = parse_problems_json(raw)
    assert len(problems) == 1
    assert problems[0].title == "Idade de Camila"
    assert problems[0].time_limit == 2.0


def test_parse_invalid_json_returns_empty():
    """Validates that invalid JSON or empty responses return [] without crashing."""
    assert parse_problems_json("This is not json") == []
    assert parse_problems_json("") == []
    assert parse_problems_json("   ") == []
    assert parse_problems_json("[{invalid json") == []
