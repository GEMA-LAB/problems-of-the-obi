# -*- coding: utf-8 -*-
"""Testes unitarios para o modulo de normalizacao e correspondencia (matcher.py)."""

from pathlib import Path
import pytest
from src.models import QuestionFolder
from src.processor.matcher import normalize_name, ResourceMatcher


def test_normalize_name_basic():
    assert normalize_name("Cabo de Guerra") == "cabodeguerra"
    assert normalize_name("Avioes de Papel!") == "avioesdepapel"
    assert normalize_name("Super-Heroi_123") == "superheroi123"
    assert normalize_name("A E I O U c a k") == "aeioucak"
    assert normalize_name("   ") == ""


def test_normalize_name_accents():
    assert normalize_name("\u00c1\u00c9\u00cd\u00d3\u00da \u00e7\u00e3o") == "aeioucao"
    assert normalize_name("Avi\u00f5es de Papel") == "avioesdepapel"
    assert normalize_name("P\u00e3o_a-Queijo") == "paoaqueijo"


def test_find_gabarito_exact_match(tmp_path):
    gabaritos_dir = tmp_path / "gabaritos"
    (gabaritos_dir / "2023" / "pj").mkdir(parents=True)
    zip_file = gabaritos_dir / "2023" / "pj" / "Cabo de Guerra.zip"
    zip_file.write_bytes(b"PK00")

    matcher = ResourceMatcher(gabaritos_dir=gabaritos_dir, codigo_dir=tmp_path / "codigo")
    question = QuestionFolder(
        path=tmp_path / "output" / "2023" / "pj" / "Cabo de Guerra",
        ano=2023,
        nivel="pj",
        titulo="Cabo de Guerra",
        titulo_normalizado="cabodeguerra",
    )
    result = matcher.find_gabarito(question)
    assert result is not None
    assert result.path_zip == zip_file
    assert result.ano == 2023
    assert result.nivel == "pj"


def test_find_gabarito_accent_and_space_insensitive(tmp_path):
    gabaritos_dir = tmp_path / "gabaritos"
    (gabaritos_dir / "2022" / "p1").mkdir(parents=True)
    zip_file = gabaritos_dir / "2022" / "p1" / "avioes_de_papel.zip"
    zip_file.write_bytes(b"PK00")

    matcher = ResourceMatcher(gabaritos_dir=gabaritos_dir, codigo_dir=tmp_path / "codigo")
    question = QuestionFolder(
        path=tmp_path / "output" / "2022" / "p1" / "Avioes de Papel",
        ano=2022,
        nivel="p1",
        titulo="Avi\u00f5es de Papel",
        titulo_normalizado="avioesdepapel",
    )
    result = matcher.find_gabarito(question)
    assert result is not None
    assert result.path_zip == zip_file


def test_find_gabarito_not_found(tmp_path):
    gabaritos_dir = tmp_path / "gabaritos"
    gabaritos_dir.mkdir(parents=True)
    matcher = ResourceMatcher(gabaritos_dir=gabaritos_dir, codigo_dir=tmp_path / "codigo")
    question = QuestionFolder(
        path=tmp_path / "output" / "2023" / "pj" / "Inexistente",
        ano=2023,
        nivel="pj",
        titulo="Inexistente",
        titulo_normalizado="inexistente",
    )
    result = matcher.find_gabarito(question)
    assert result is None


def test_find_solutions_multiple(tmp_path):
    codigo_dir = tmp_path / "codigo"
    (codigo_dir / "2023" / "pj").mkdir(parents=True)
    sol1 = codigo_dir / "2023" / "pj" / "cabo.cpp"
    sol1.write_text("int main() {}")
    sol2 = codigo_dir / "2023" / "pj" / "cabo.py"
    sol2.write_text("print(1)")
    sol_outro = codigo_dir / "2023" / "pj" / "outro.py"
    sol_outro.write_text("print(2)")

    matcher = ResourceMatcher(gabaritos_dir=tmp_path / "gabaritos", codigo_dir=codigo_dir)
    question = QuestionFolder(
        path=tmp_path / "output" / "2023" / "pj" / "Cabo de Guerra",
        ano=2023,
        nivel="pj",
        titulo="Cabo de Guerra",
        titulo_normalizado="cabodeguerra",
    )
    results = matcher.find_solutions(matcher_alias="cabo", question=question)
    assert len(results) == 2
    extensions = {r.linguagem for r in results}
    assert "cpp" in extensions
    assert "py" in extensions
