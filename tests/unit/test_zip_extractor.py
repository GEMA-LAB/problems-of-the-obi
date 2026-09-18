# -*- coding: utf-8 -*-
"""Testes unitarios para o modulo de descompactacao segura (zip_extractor.py)."""
from pathlib import Path
import zipfile
import pytest
from src.processor.zip_extractor import ZipExtractor


def test_extract_valid_zip(tmp_path):
    zip_path = tmp_path / "testes.zip"
    with zipfile.ZipFile(zip_path, "w") as zf:
        zf.writestr("1.in", "1 2 3\n")
        zf.writestr("1.out", "6\n")

    target_dir = tmp_path / "output"
    extractor = ZipExtractor()
    success = extractor.extract_test_cases(zip_path, target_dir)

    assert success is True
    assert (target_dir / "1.in").exists()
    assert (target_dir / "1.out").exists()
    assert (target_dir / "1.in").read_text() == "1 2 3\n"


def test_extract_corrupted_zip(tmp_path):
    corrupt_zip = tmp_path / "corrupto.zip"
    corrupt_zip.write_bytes(b"NOT_A_ZIP_FILE")

    target_dir = tmp_path / "output"
    extractor = ZipExtractor()
    success = extractor.extract_test_cases(corrupt_zip, target_dir)

    assert success is False


def test_extract_nonexistent_zip(tmp_path):
    nonexistent = tmp_path / "nao-existe.zip"
    extractor = ZipExtractor()
    success = extractor.extract_test_cases(nonexistent, tmp_path / "out")
    assert success is False


def test_extract_zip_slip_protection(tmp_path):
    zip_path = tmp_path / "malicious.zip"
    with zipfile.ZipFile(zip_path, "w") as zf:
        zf.writestr("../../malicious.txt", "hack")
        zf.writestr("safe.in", "safe")

    target_dir = tmp_path / "safe_dir"
    target_dir.mkdir()
    extractor = ZipExtractor()
    success = extractor.extract_test_cases(zip_path, target_dir)

    assert success is True
    assert (target_dir / "safe.in").exists()
    assert not (tmp_path / "malicious.txt").exists()


def test_extract_solutions_zip(tmp_path):
    zip_sol = tmp_path / "solucoes.zip"
    with zipfile.ZipFile(zip_sol, "w") as zf:
        zf.writestr("cabo.cpp", "int main() {}")
        zf.writestr("cabo.py", "print(1)")
        zf.writestr("cabo.exe", "binary")

    target_dir = tmp_path / "solutions"
    extractor = ZipExtractor()
    results = extractor.extract_solutions(zip_sol, target_dir)

    assert len(results) == 2
    exts = {p.suffix for p in results}
    assert ".cpp" in exts
    assert ".py" in exts
    assert not (target_dir / "cabo.exe").exists()
