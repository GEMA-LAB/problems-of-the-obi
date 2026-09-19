"""Unit tests for PythonDatasetBuilder."""
import json
from pathlib import Path
import pytest
from src.processor.python_dataset_builder import PythonDatasetBuilder


def test_is_python_file():
    builder = PythonDatasetBuilder()
    assert builder.is_python_file(Path("solution.py")) is True
    assert builder.is_python_file(Path("solution.py3")) is True
    assert builder.is_python_file(Path("SOLUTION.PY")) is True
    assert builder.is_python_file(Path("solution.cpp")) is False
    assert builder.is_python_file(Path("solution.c")) is False
    assert builder.is_python_file(Path("solution.java")) is False
    assert builder.is_python_file(Path("solution.js")) is False
    assert builder.is_python_file(Path("problem.json")) is False


def test_has_python_solution(tmp_path):
    builder = PythonDatasetBuilder()

    # Case 1: Question with python solution
    q1 = tmp_path / "q1"
    sol1 = q1 / "solutions"
    sol1.mkdir(parents=True)
    (sol1 / "sol.py").write_text("print('hello')")
    (sol1 / "sol.cpp").write_text("int main() {}")

    has_py, py_files = builder.has_python_solution(q1)
    assert has_py is True
    assert len(py_files) == 1
    assert py_files[0].name == "sol.py"

    # Case 2: Question with only non-python solutions
    q2 = tmp_path / "q2"
    sol2 = q2 / "solutions"
    sol2.mkdir(parents=True)
    (sol2 / "sol.cpp").write_text("int main() {}")
    (sol2 / "sol.java").write_text("class Sol {}")

    has_py, py_files = builder.has_python_solution(q2)
    assert has_py is False
    assert len(py_files) == 0

    # Case 3: Question without solutions dir
    q3 = tmp_path / "q3"
    q3.mkdir()
    has_py, py_files = builder.has_python_solution(q3)
    assert has_py is False
    assert len(py_files) == 0


def test_export_question(tmp_path):
    builder = PythonDatasetBuilder()

    src_q = tmp_path / "src" / "2024" / "pj" / "Jogo"
    src_sol = src_q / "solutions"
    src_tests = src_q / "test_cases"
    src_in = src_tests / "inputs"
    src_out = src_tests / "outputs"

    src_sol.mkdir(parents=True)
    src_in.mkdir(parents=True)
    src_out.mkdir(parents=True)

    # Populate source question
    (src_q / "problem.json").write_text(json.dumps({"title": "Jogo", "year": 2024}))
    (src_sol / "jogo_py.py").write_text("print('python')")
    (src_sol / "jogo_cpp.cpp").write_text("int main() {}")
    (src_sol / "jogo_java.java").write_text("class Jogo {}")
    (src_in / "1.in").write_text("10\n")
    (src_out / "1.out").write_text("20\n")

    target_q = tmp_path / "target" / "2024" / "pj" / "Jogo"
    stats = builder.export_question(src_q, target_q)

    assert stats["sucesso"] is True
    assert stats["arquivos_python"] == 1
    assert stats["casos_teste"] == 2

    # Check target files
    assert (target_q / "problem.json").exists()
    assert (target_q / "solutions" / "jogo_py.py").exists()
    assert not (target_q / "solutions" / "jogo_cpp.cpp").exists()
    assert not (target_q / "solutions" / "jogo_java.java").exists()
    assert (target_q / "test_cases" / "inputs" / "1.in").exists()
    assert (target_q / "test_cases" / "outputs" / "1.out").exists()


def test_build_dataset(tmp_path):
    builder = PythonDatasetBuilder()

    source_dir = tmp_path / "output_with_code"
    target_dir = tmp_path / "dataset_obi_python"

    # Setup Question 1 (with python)
    q1 = source_dir / "2024" / "pj" / "Questao1"
    (q1 / "solutions").mkdir(parents=True)
    (q1 / "test_cases" / "inputs").mkdir(parents=True)
    (q1 / "test_cases" / "outputs").mkdir(parents=True)
    (q1 / "problem.json").write_text(json.dumps({"title": "Questao1", "year": 2024, "level": "pj"}))
    (q1 / "solutions" / "q1.py").write_text("pass")
    (q1 / "solutions" / "q1.cpp").write_text("pass")
    (q1 / "test_cases" / "inputs" / "1.in").write_text("1")
    (q1 / "test_cases" / "outputs" / "1.out").write_text("1")

    # Setup Question 2 (only cpp - should be skipped)
    q2 = source_dir / "2024" / "pj" / "Questao2"
    (q2 / "solutions").mkdir(parents=True)
    (q2 / "test_cases" / "inputs").mkdir(parents=True)
    (q2 / "test_cases" / "outputs").mkdir(parents=True)
    (q2 / "problem.json").write_text(json.dumps({"title": "Questao2", "year": 2024, "level": "pj"}))
    (q2 / "solutions" / "q2.cpp").write_text("pass")

    # Setup Question 3 (2023 p1 with python)
    q3 = source_dir / "2023" / "p1" / "Questao3"
    (q3 / "solutions").mkdir(parents=True)
    (q3 / "test_cases" / "inputs").mkdir(parents=True)
    (q3 / "test_cases" / "outputs").mkdir(parents=True)
    (q3 / "problem.json").write_text(json.dumps({"title": "Questao3", "year": 2023, "level": "p1"}))
    (q3 / "solutions" / "q3.py3").write_text("pass")

    stats = builder.build_dataset(source_dir, target_dir)

    assert stats["total_questoes_analisadas"] == 3
    assert stats["questoes_com_python"] == 2
    assert stats["questoes_exportadas"] == 2

    # Verify target structure
    assert (target_dir / "2024" / "pj" / "Questao1" / "problem.json").exists()
    assert (target_dir / "2024" / "pj" / "Questao1" / "solutions" / "q1.py").exists()
    assert not (target_dir / "2024" / "pj" / "Questao1" / "solutions" / "q1.cpp").exists()

    assert not (target_dir / "2024" / "pj" / "Questao2").exists()

    assert (target_dir / "2023" / "p1" / "Questao3" / "problem.json").exists()
    assert (target_dir / "2023" / "p1" / "Questao3" / "solutions" / "q3.py3").exists()
