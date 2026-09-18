"""Testes unitarios para os modelos de dominio de organizacao de questoes."""
from pathlib import Path
import pytest
from dataclasses import FrozenInstanceError
from src.models import (
    OrganizeConfig,
    OrganizeResult,
    QuestionFolder,
    SolutionSource,
    TestCasePair,
    TestCaseSource,
)


def test_question_folder_immutable():
    qf = QuestionFolder(
        path=Path("output_with_code/2023/pj/cabo"),
        ano=2023,
        nivel="pj",
        titulo="Cabo de Guerra",
        titulo_normalizado="cabodeguerra",
    )
    assert qf.ano == 2023
    assert qf.nivel == "pj"
    assert qf.titulo_normalizado == "cabodeguerra"
    with pytest.raises(FrozenInstanceError):
        qf.ano = 2024


def test_test_case_pair_immutable():
    pair = TestCasePair(
        id=1,
        input_file=Path("test_cases/inputs/1.in"),
        output_file=Path("test_cases/outputs/1.out"),
    )
    assert pair.id == 1
    assert pair.input_file.name == "1.in"
    assert pair.output_file.name == "1.out"
    with pytest.raises(FrozenInstanceError):
        pair.id = 2


def test_test_case_source_and_solution_source():
    ts = TestCaseSource(
        path_zip=Path("gabaritos/2023/pj/Cabo de guerra.zip"),
        ano=2023,
        nivel="pj",
        nome_normalizado="cabodeguerra",
    )
    assert ts.path_zip.suffix == ".zip"
    ss = SolutionSource(
        path_arquivo=Path("codigo/2023/pj/cabo.java"),
        ano=2023,
        nivel="pj",
        nome_normalizado="cabo",
        linguagem="java",
    )
    assert ss.linguagem == "java"
    with pytest.raises(FrozenInstanceError):
        ts.ano = 2020


def test_organize_config_defaults():
    cfg = OrganizeConfig()
    assert cfg.pasta_output == Path("output_with_code")
    assert cfg.pasta_gabaritos == Path("gabaritos")
    assert cfg.pasta_codigo == Path("codigo")
    assert cfg.force is False


def test_organize_result_defaults():
    res = OrganizeResult(questao="Cabo de Guerra")
    assert res.questao == "Cabo de Guerra"
    assert res.test_pairs == []
    assert res.solutions_count == 0
    assert res.status == "sem_recursos"
