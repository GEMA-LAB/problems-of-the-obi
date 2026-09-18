# -*- coding: utf-8 -*-
"""Testes unitarios para o modulo de limpeza e expurgacao segura (cleaner.py)."""
from pathlib import Path
import pytest
from src.models import TestCasePair
from src.processor.cleaner import DatasetCleaner


def test_clean_residuals_removes_binaries_and_temp(tmp_path):
    tc_dir = tmp_path / "test_cases"
    (tc_dir / "inputs").mkdir(parents=True)
    (tc_dir / "outputs").mkdir(parents=True)
    (tc_dir / "lixo_dir").mkdir(parents=True)

    in1 = tc_dir / "inputs" / "1.in"
    in1.write_text("in")
    out1 = tc_dir / "outputs" / "1.out"
    out1.write_text("out")

    root_in1 = tc_dir / "1.in"
    root_in1.write_text("in")
    root_out1 = tc_dir / "1.out"
    root_out1.write_text("out")

    # Residuos que devem ser deletados
    exe_file = tc_dir / "solucao.exe"
    exe_file.write_text("binary")
    o_file = tc_dir / "teste.o"
    o_file.write_text("object")
    lixo_file = tc_dir / "lixo_dir" / "sobra.txt"
    lixo_file.write_text("sobra")

    cleaner = DatasetCleaner()
    valid_pairs = [TestCasePair(id=1, input_file=in1, output_file=out1)]
    cleaner.clean_test_cases_residuals(tc_dir, valid_pairs)

    # Verifica o que deve permanecer
    assert in1.exists()
    assert out1.exists()
    assert root_in1.exists()
    assert root_out1.exists()

    # Verifica o que deve ter sido expurgado
    assert not exe_file.exists()
    assert not o_file.exists()
    assert not (tc_dir / "lixo_dir").exists()


def test_validate_and_cleanup_question_with_tests(tmp_path):
    q_dir = tmp_path / "output" / "2023" / "pj" / "Cabo"
    q_dir.mkdir(parents=True)
    (q_dir / "problem.json").write_text('{"title": "Cabo"}')
    (q_dir / "imgs").mkdir()
    (q_dir / "imgs" / "diagrama.png").write_text("png")

    tc_dir = q_dir / "test_cases" / "inputs"
    tc_dir.mkdir(parents=True)
    in_file = tc_dir / "1.in"
    in_file.write_text("1")
    out_dir = q_dir / "test_cases" / "outputs"
    out_dir.mkdir(parents=True)
    out_file = out_dir / "1.out"
    out_file.write_text("1")

    valid_pairs = [TestCasePair(id=1, input_file=in_file, output_file=out_file)]
    cleaner = DatasetCleaner()
    kept = cleaner.validate_and_cleanup_question(q_dir, valid_pairs)

    assert kept is True
    assert q_dir.exists()
    assert (q_dir / "problem.json").exists()
    assert (q_dir / "imgs" / "diagrama.png").exists()


def test_validate_and_cleanup_question_without_tests(tmp_path):
    q_dir = tmp_path / "output" / "2023" / "pj" / "SemTestes"
    q_dir.mkdir(parents=True)
    (q_dir / "problem.json").write_text('{"title": "SemTestes"}')

    cleaner = DatasetCleaner()
    kept = cleaner.validate_and_cleanup_question(q_dir, valid_pairs=[])

    assert kept is False
    assert not q_dir.exists()
