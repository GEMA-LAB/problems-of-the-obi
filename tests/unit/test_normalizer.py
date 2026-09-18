# -*- coding: utf-8 -*-
"""Testes unitarios para o modulo de normalizacao de casos de teste (normalizer.py)."""
from pathlib import Path
import pytest
from src.processor.normalizer import TestCaseNormalizer


def test_pair_files_with_same_stem(tmp_path):
    raw_dir = tmp_path / "raw"
    raw_dir.mkdir()
    (raw_dir / "teste1.in").write_text("1 2")
    (raw_dir / "teste1.out").write_text("3")
    (raw_dir / "teste2.in").write_text("4 5")
    (raw_dir / "teste2.sol").write_text("9")

    normalizer = TestCaseNormalizer()
    pairs = normalizer.scan_and_pair(raw_dir)

    assert len(pairs) == 2
    in_names = [p[0].name for p in pairs]
    assert "teste1.in" in in_names
    assert "teste2.in" in in_names


def test_pair_files_in_numbered_folders(tmp_path):
    raw_dir = tmp_path / "raw"
    (raw_dir / "1").mkdir(parents=True)
    (raw_dir / "1" / "in").write_text("10")
    (raw_dir / "1" / "out").write_text("20")

    (raw_dir / "2").mkdir(parents=True)
    (raw_dir / "2" / "in").write_text("30")
    (raw_dir / "2" / "out").write_text("40")

    normalizer = TestCaseNormalizer()
    pairs = normalizer.scan_and_pair(raw_dir)

    assert len(pairs) == 2
    assert pairs[0][0].parent.name == "1"
    assert pairs[1][0].parent.name == "2"


def test_reject_orphan_inputs_and_outputs(tmp_path):
    raw_dir = tmp_path / "raw"
    raw_dir.mkdir()
    (raw_dir / "1.in").write_text("1")
    (raw_dir / "1.out").write_text("1")
    (raw_dir / "2.in").write_text("2")  # Sem 2.out
    (raw_dir / "3.out").write_text("3")  # Sem 3.in

    normalizer = TestCaseNormalizer()
    pairs = normalizer.scan_and_pair(raw_dir)

    assert len(pairs) == 1
    assert pairs[0][0].name == "1.in"
    assert pairs[0][1].name == "1.out"


def test_normalize_to_destination(tmp_path):
    raw_dir = tmp_path / "raw"
    raw_dir.mkdir()
    (raw_dir / "exA.in").write_text("10")
    (raw_dir / "exA.out").write_text("20")
    (raw_dir / "exB.in").write_text("30")
    (raw_dir / "exB.out").write_text("40")

    normalizer = TestCaseNormalizer()
    pairs = normalizer.scan_and_pair(raw_dir)

    dest_dir = tmp_path / "test_cases"
    result_pairs = normalizer.normalize_to_destination(pairs, dest_dir)

    assert len(result_pairs) == 2
    assert result_pairs[0].id == 1
    assert result_pairs[0].input_file.name == "1.in"
    assert result_pairs[0].output_file.name == "1.out"
    assert (dest_dir / "inputs" / "1.in").exists()
    assert (dest_dir / "outputs" / "1.out").exists()
    assert (dest_dir / "inputs" / "2.in").exists()
    assert (dest_dir / "outputs" / "2.out").exists()
    assert not (dest_dir / "1.in").exists()
    assert not (dest_dir / "1.out").exists()
    assert not (dest_dir / "2.in").exists()
    assert not (dest_dir / "2.out").exists()


def test_empty_directory(tmp_path):
    empty_dir = tmp_path / "empty"
    empty_dir.mkdir()
    normalizer = TestCaseNormalizer()
    pairs = normalizer.scan_and_pair(empty_dir)
    assert pairs == []
