# -*- coding: utf-8 -*-
"""Testes unitarios para o orquestrador QuestionsOrganizer (questions_organizer.py)."""
import json
import zipfile
from pathlib import Path
import pytest
from src.models import OrganizeConfig, QuestionFolder
from src.processor.questions_organizer import QuestionsOrganizer


def test_discover_questions_with_metadata(tmp_path):
    output_dir = tmp_path / "output_with_code"
    q1 = output_dir / "2023" / "pj" / "Cabo"
    q1.mkdir(parents=True)
    (q1 / "problem.json").write_text(
        json.dumps({"title": "Cabo de Guerra", "year": 2023, "level": "pj"}),
        encoding="utf-8"
    )

    q2 = output_dir / "2022" / "p1" / "Avioes"
    q2.mkdir(parents=True)
    (q2 / "problem.json").write_text(
        json.dumps({"title": "Aviões de Papel", "year": 2022, "level": "p1"}),
        encoding="utf-8"
    )

    organizer = QuestionsOrganizer()
    all_q = organizer.discover_questions(output_dir)
    assert len(all_q) == 2

    # Teste de filtro por ano
    q_2023 = organizer.discover_questions(output_dir, ano_filtro=2023)
    assert len(q_2023) == 1
    assert q_2023[0].ano == 2023

    # Teste de filtro por nivel
    q_p1 = organizer.discover_questions(output_dir, nivel_filtro="p1")
    assert len(q_p1) == 1
    assert q_p1[0].nivel == "p1"


def test_organize_question_full_flow(tmp_path):
    output_dir = tmp_path / "output_with_code"
    gabaritos_dir = tmp_path / "gabaritos"
    codigo_dir = tmp_path / "codigo"

    # 1. Cria pasta da questao
    q_path = output_dir / "2023" / "pj" / "Cabo de Guerra"
    q_path.mkdir(parents=True)
    (q_path / "problem.json").write_text(
        json.dumps({"title": "Cabo de Guerra", "year": 2023, "level": "pj"}),
        encoding="utf-8"
    )

    # 2. Cria gabarito ZIP
    (gabaritos_dir / "2023" / "pj").mkdir(parents=True)
    zip_path = gabaritos_dir / "2023" / "pj" / "Cabo de Guerra.zip"
    with zipfile.ZipFile(zip_path, "w") as zf:
        zf.writestr("1.in", "10 20\n")
        zf.writestr("1.out", "30\n")
        zf.writestr("2.in", "5 5\n")
        zf.writestr("2.out", "10\n")
        zf.writestr("sobra.exe", "bin")

    # 3. Cria codigo oficial
    (codigo_dir / "2023" / "pj").mkdir(parents=True)
    (codigo_dir / "2023" / "pj" / "cabo.cpp").write_text("int main() {}")

    config = OrganizeConfig(
        pasta_output=output_dir,
        pasta_gabaritos=gabaritos_dir,
        pasta_codigo=codigo_dir,
        force=False,
    )

    organizer = QuestionsOrganizer()
    q_folder = QuestionFolder(
        path=q_path,
        ano=2023,
        nivel="pj",
        titulo="Cabo de Guerra",
        titulo_normalizado="cabodeguerra",
    )

    result = organizer.organize_question(q_folder, config)

    assert result.status == "sucesso"
    assert len(result.test_pairs) == 2
    assert result.solutions_count == 1
    assert (q_path / "test_cases" / "inputs" / "1.in").exists()
    assert (q_path / "test_cases" / "outputs" / "1.out").exists()
    assert (q_path / "test_cases" / "inputs" / "2.in").exists()
    assert (q_path / "test_cases" / "outputs" / "2.out").exists()
    assert not (q_path / "test_cases" / "sobra.exe").exists()
    assert not (q_path / "test_cases" / "1.in").exists()
    assert not (q_path / "test_cases" / "1.out").exists()
    assert (q_path / "solutions" / "cabo.cpp").exists()
    assert (q_path / "problem.json").exists()


def test_organize_question_idempotence(tmp_path):
    output_dir = tmp_path / "output_with_code"
    q_path = output_dir / "2023" / "pj" / "Cabo de Guerra"
    (q_path / "test_cases" / "inputs").mkdir(parents=True)
    (q_path / "test_cases" / "outputs").mkdir(parents=True)
    (q_path / "test_cases" / "inputs" / "1.in").write_text("1")
    (q_path / "test_cases" / "outputs" / "1.out").write_text("1")
    (q_path / "problem.json").write_text('{"title": "Cabo de Guerra"}')

    config = OrganizeConfig(pasta_output=output_dir, force=False)
    organizer = QuestionsOrganizer()
    q_folder = QuestionFolder(
        path=q_path,
        ano=2023,
        nivel="pj",
        titulo="Cabo de Guerra",
        titulo_normalizado="cabodeguerra",
    )

    result = organizer.organize_question(q_folder, config)
    assert result.status == "ignorado_idempotente"


def test_organize_question_without_tests_kept(tmp_path):
    output_dir = tmp_path / "output_with_code"
    q_path = output_dir / "2023" / "pj" / "SemTestes"
    q_path.mkdir(parents=True)
    (q_path / "problem.json").write_text('{"title": "SemTestes"}')

    config = OrganizeConfig(
        pasta_output=output_dir,
        pasta_gabaritos=tmp_path / "gabaritos",
        pasta_codigo=tmp_path / "codigo",
        force=False,
    )
    organizer = QuestionsOrganizer()
    q_folder = QuestionFolder(
        path=q_path,
        ano=2023,
        nivel="pj",
        titulo="SemTestes",
        titulo_normalizado="semtestes",
    )

    result = organizer.organize_question(q_folder, config)
    assert result.status == "sem_testes"
    assert q_path.exists()
    assert (q_path / "problem.json").exists()


def test_organize_all_summary(tmp_path):
    output_dir = tmp_path / "output_with_code"
    gabaritos_dir = tmp_path / "gabaritos"
    codigo_dir = tmp_path / "codigo"

    # Questao 1: valida com testes e solucao
    q1_path = output_dir / "2023" / "pj" / "Cabo"
    q1_path.mkdir(parents=True)
    (q1_path / "problem.json").write_text(json.dumps({"title": "Cabo", "year": 2023, "level": "pj"}))
    (gabaritos_dir / "2023" / "pj").mkdir(parents=True)
    with zipfile.ZipFile(gabaritos_dir / "2023" / "pj" / "Cabo.zip", "w") as zf:
        zf.writestr("1.in", "1")
        zf.writestr("1.out", "1")
    (codigo_dir / "2023" / "pj").mkdir(parents=True)
    (codigo_dir / "2023" / "pj" / "cabo.py").write_text("print(1)")

    # Questao 2: sem testes
    q2_path = output_dir / "2023" / "pj" / "Invalida"
    q2_path.mkdir(parents=True)
    (q2_path / "problem.json").write_text(json.dumps({"title": "Invalida", "year": 2023, "level": "pj"}))

    config = OrganizeConfig(
        pasta_output=output_dir,
        pasta_gabaritos=gabaritos_dir,
        pasta_codigo=codigo_dir,
        force=False,
    )
    organizer = QuestionsOrganizer()
    stats = organizer.organize_all(config, ano_filtro=2023, nivel_filtro="pj")

    assert stats["total_encontradas"] == 2
    assert stats["sucesso"] == 1
    assert stats["sem_testes"] == 1
    assert stats["removidas_sem_testes"] == 1
    assert stats["total_testes"] == 1
    assert stats["total_solucoes"] == 1
    assert q2_path.exists()
    assert q1_path.exists()


