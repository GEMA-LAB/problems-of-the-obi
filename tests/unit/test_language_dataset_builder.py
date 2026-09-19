"""Unit tests for LanguageDatasetBuilder."""
import json
from pathlib import Path
import pytest
from src.processor.language_dataset_builder import LanguageDatasetBuilder


def test_normalize_language():
    builder = LanguageDatasetBuilder()
    assert builder.normalize_language("python") == "python"
    assert builder.normalize_language("py") == "python"
    assert builder.normalize_language("py3") == "python"
    assert builder.normalize_language("cpp") == "cpp"
    assert builder.normalize_language("c++") == "cpp"
    assert builder.normalize_language("cc") == "cpp"
    assert builder.normalize_language("cxx") == "cpp"
    assert builder.normalize_language("c") == "c"
    assert builder.normalize_language("java") == "java"
    assert builder.normalize_language("pascal") == "pascal"
    assert builder.normalize_language("pas") == "pascal"
    assert builder.normalize_language("javascript") == "javascript"
    assert builder.normalize_language("js") == "javascript"

    with pytest.raises(ValueError, match="nao suportada"):
        builder.normalize_language("rust")


def test_get_language_extensions():
    builder = LanguageDatasetBuilder()
    assert builder.get_language_extensions("cpp") == {".cpp", ".cc", ".cxx"}
    assert builder.get_language_extensions("c++") == {".cpp", ".cc", ".cxx"}
    assert builder.get_language_extensions("python") == {".py", ".py3"}
    assert builder.get_language_extensions("java") == {".java"}
    assert builder.get_language_extensions("pascal") == {".pas"}
    assert builder.get_language_extensions("javascript") == {".js"}
    assert builder.get_language_extensions("c") == {".c"}


def test_get_default_target_dir():
    builder = LanguageDatasetBuilder()
    assert builder.get_default_target_dir("python") == Path("dataset_obi_python")
    assert builder.get_default_target_dir("cpp") == Path("dataset_obi_cpp")
    assert builder.get_default_target_dir("c++") == Path("dataset_obi_cpp")
    assert builder.get_default_target_dir("c") == Path("dataset_obi_c")
    assert builder.get_default_target_dir("java") == Path("dataset_obi_java")
    assert builder.get_default_target_dir("pascal") == Path("dataset_obi_pascal")
    assert builder.get_default_target_dir("javascript") == Path("dataset_obi_javascript")
    assert builder.get_default_target_dir("js") == Path("dataset_obi_javascript")


def test_is_language_file():
    builder = LanguageDatasetBuilder()
    assert builder.is_language_file(Path("sol.cpp"), "cpp") is True
    assert builder.is_language_file(Path("sol.cc"), "c++") is True
    assert builder.is_language_file(Path("sol.cxx"), "cpp") is True
    assert builder.is_language_file(Path("sol.py"), "cpp") is False
    assert builder.is_language_file(Path("sol.java"), "java") is True
    assert builder.is_language_file(Path("sol.pas"), "pascal") is True
    assert builder.is_language_file(Path("sol.js"), "javascript") is True
    assert builder.is_language_file(Path("sol.c"), "c") is True


def test_export_question_cpp(tmp_path):
    builder = LanguageDatasetBuilder()

    src_q = tmp_path / "src" / "2024" / "pj" / "Jogo"
    src_sol = src_q / "solutions"
    src_tests = src_q / "test_cases"
    src_in = src_tests / "inputs"
    src_out = src_tests / "outputs"

    src_sol.mkdir(parents=True)
    src_in.mkdir(parents=True)
    src_out.mkdir(parents=True)

    (src_q / "problem.json").write_text(json.dumps({"title": "Jogo", "year": 2024}))
    (src_sol / "jogo_py.py").write_text("print('python')")
    (src_sol / "jogo_cpp.cpp").write_text("int main() {}")
    (src_sol / "jogo_alt.cc").write_text("int main() {}")
    (src_sol / "jogo_java.java").write_text("class Jogo {}")
    (src_in / "1.in").write_text("10\n")
    (src_out / "1.out").write_text("20\n")

    target_q = tmp_path / "target" / "2024" / "pj" / "Jogo"
    stats = builder.export_question(src_q, target_q, lang="cpp")

    assert stats["sucesso"] is True
    assert stats["arquivos_solucao"] == 2
    assert stats["casos_teste"] == 2

    # Check target files: only cpp and cc
    assert (target_q / "problem.json").exists()
    assert (target_q / "solutions" / "jogo_cpp.cpp").exists()
    assert (target_q / "solutions" / "jogo_alt.cc").exists()
    assert not (target_q / "solutions" / "jogo_py.py").exists()
    assert not (target_q / "solutions" / "jogo_java.java").exists()


def test_build_dataset_cpp(tmp_path):
    builder = LanguageDatasetBuilder()

    source_dir = tmp_path / "output_with_code"
    target_dir = tmp_path / "dataset_obi_cpp"

    # Setup Question 1 (with cpp)
    q1 = source_dir / "2024" / "pj" / "Questao1"
    (q1 / "solutions").mkdir(parents=True)
    (q1 / "test_cases" / "inputs").mkdir(parents=True)
    (q1 / "test_cases" / "outputs").mkdir(parents=True)
    (q1 / "problem.json").write_text(json.dumps({"title": "Questao1", "year": 2024, "level": "pj"}))
    (q1 / "solutions" / "q1.cpp").write_text("int main() {}")
    (q1 / "test_cases" / "inputs" / "1.in").write_text("1")
    (q1 / "test_cases" / "outputs" / "1.out").write_text("1")

    # Setup Question 2 (only python - should be skipped for cpp)
    q2 = source_dir / "2024" / "pj" / "Questao2"
    (q2 / "solutions").mkdir(parents=True)
    (q2 / "test_cases" / "inputs").mkdir(parents=True)
    (q2 / "test_cases" / "outputs").mkdir(parents=True)
    (q2 / "problem.json").write_text(json.dumps({"title": "Questao2", "year": 2024, "level": "pj"}))
    (q2 / "solutions" / "q2.py").write_text("pass")

    stats = builder.build_dataset(source_dir, target_dir, language="c++")

    assert stats["linguagem"] == "cpp"
    assert stats["total_questoes_analisadas"] == 2
    assert stats["questoes_com_solucao"] == 1
    assert stats["questoes_exportadas"] == 1

    assert (target_dir / "2024" / "pj" / "Questao1" / "problem.json").exists()
    assert (target_dir / "2024" / "pj" / "Questao1" / "solutions" / "q1.cpp").exists()
    assert not (target_dir / "2024" / "pj" / "Questao2").exists()
