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


def test_find_solutions_prefix_and_author_variants(tmp_path):
    codigo_dir = tmp_path / "codigo"
    (codigo_dir / "2025" / "p1").mkdir(parents=True)
    (codigo_dir / "2025" / "p1" / "recarga_carro.cpp").write_text("int main() {}")
    (codigo_dir / "2025" / "p1" / "recarga_lobo_bb.cpp").write_text("int main() {}")
    (codigo_dir / "2025" / "p1" / "recarga_pedro_union_find.cpp").write_text("int main() {}")
    (codigo_dir / "2025" / "p1" / "outro_problema.cpp").write_text("int main() {}")

    matcher = ResourceMatcher(gabaritos_dir=tmp_path / "gabaritos", codigo_dir=codigo_dir)
    question = QuestionFolder(
        path=tmp_path / "output_with_code" / "2025" / "p1" / "Recarga",
        ano=2025,
        nivel="p1",
        titulo="Recarga",
        titulo_normalizado=normalize_name("Recarga"),
    )
    results = matcher.find_solutions(question=question)
    assert len(results) == 3
    names = {r.path_arquivo.name for r in results}
    assert "recarga_carro.cpp" in names
    assert "recarga_lobo_bb.cpp" in names
    assert "recarga_pedro_union_find.cpp" in names


def test_find_solutions_token_intersection_and_stopwords(tmp_path):
    codigo_dir = tmp_path / "codigo"
    (codigo_dir / "2025" / "p1").mkdir(parents=True)
    (codigo_dir / "2025" / "p1" / "redes_1_freq_java.java").write_text("class Redes {}")
    (codigo_dir / "2025" / "p1" / "redes_2_dict_py.py").write_text("print(1)")
    (codigo_dir / "2025" / "p1" / "redes_andre.cpp").write_text("int main() {}")
    (codigo_dir / "2025" / "p1" / "redes_reference.cpp").write_text("int main() {}")
    (codigo_dir / "2025" / "p1" / "diagonal.java").write_text("class Diagonal {}")

    matcher = ResourceMatcher(gabaritos_dir=tmp_path / "gabaritos", codigo_dir=codigo_dir)
    question = QuestionFolder(
        path=tmp_path / "output_with_code" / "2025" / "p1" / "Redes de Descanso",
        ano=2025,
        nivel="p1",
        titulo="Redes de Descanso",
        titulo_normalizado=normalize_name("Redes de Descanso"),
    )
    results = matcher.find_solutions(question=question)
    assert len(results) == 4
    names = {r.path_arquivo.name for r in results}
    assert "redes_1_freq_java.java" in names
    assert "redes_andre.cpp" in names


def test_find_solutions_feira_de_artesanato(tmp_path):
    codigo_dir = tmp_path / "codigo"
    (codigo_dir / "2025" / "p1").mkdir(parents=True)
    (codigo_dir / "2025" / "p1" / "feira.java").write_text("class Feira {}")
    (codigo_dir / "2025" / "p1" / "feira_artesanato_cpp.cpp").write_text("int main() {}")
    (codigo_dir / "2025" / "p1" / "feira_artesanato_py.py").write_text("print(1)")

    matcher = ResourceMatcher(gabaritos_dir=tmp_path / "gabaritos", codigo_dir=codigo_dir)
    question = QuestionFolder(
        path=tmp_path / "output_with_code" / "2025" / "p1" / "Feira de Artesanato",
        ano=2025,
        nivel="p1",
        titulo="Feira de Artesanato",
        titulo_normalizado=normalize_name("Feira de Artesanato"),
    )
    results = matcher.find_solutions(question=question)
    assert len(results) == 3


def test_find_solutions_disambiguation(tmp_path):
    codigo_dir = tmp_path / "codigo"
    (codigo_dir / "2025" / "p1").mkdir(parents=True)
    (codigo_dir / "2025" / "p1" / "fila.java").write_text("class Fila {}")
    (codigo_dir / "2025" / "p1" / "fila_c.c").write_text("int main() {}")
    (codigo_dir / "2025" / "p1" / "fila_cantina.cpp").write_text("int main() {}")

    matcher = ResourceMatcher(gabaritos_dir=tmp_path / "gabaritos", codigo_dir=codigo_dir)
    q_fila = QuestionFolder(
        path=tmp_path / "output_with_code" / "2025" / "p1" / "Fila",
        ano=2025,
        nivel="p1",
        titulo="Fila",
        titulo_normalizado=normalize_name("Fila"),
    )
    q_cantina = QuestionFolder(
        path=tmp_path / "output_with_code" / "2025" / "p1" / "Fila na Cantina",
        ano=2025,
        nivel="p1",
        titulo="Fila na Cantina",
        titulo_normalizado=normalize_name("Fila na Cantina"),
    )
    q_fila.path.mkdir(parents=True, exist_ok=True)
    q_cantina.path.mkdir(parents=True, exist_ok=True)

    res_fila = matcher.find_solutions(question=q_fila)
    res_cantina = matcher.find_solutions(question=q_cantina)

    fila_names = {r.path_arquivo.name for r in res_fila}
    cantina_names = {r.path_arquivo.name for r in res_cantina}

    assert "fila.java" in fila_names
    assert "fila_c.c" in fila_names
    assert "fila_cantina.cpp" in cantina_names
    assert "fila_cantina.cpp" not in fila_names

