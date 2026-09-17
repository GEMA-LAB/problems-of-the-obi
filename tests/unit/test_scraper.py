"""Unit tests for src.crawler.scraper."""
import pytest
from src.crawler.scraper import ObiScraper, CadernoLink


def test_infer_level_or_phase_junior():
    scraper = ObiScraper()
    nivel = scraper.infer_level_or_phase(
        url_path="fase1/programacao/cadernos/",
        link_text="Caderno de Tarefas - Programação Júnior",
        filename="caderno_pj.pdf"
    )
    assert nivel == "pj"


def test_infer_level_or_phase_nivel1():
    scraper = ObiScraper()
    nivel = scraper.infer_level_or_phase(
        url_path="fase1/programacao/cadernos/",
        link_text="Caderno de Tarefas - Programação Nível 1",
        filename="prova_p1.pdf"
    )
    assert nivel == "p1"


def test_infer_level_or_phase_nivel2():
    scraper = ObiScraper()
    nivel = scraper.infer_level_or_phase(
        url_path="fase2/programacao/",
        link_text="Caderno Nível 2",
        filename="caderno2.pdf"
    )
    assert nivel == "p2"


def test_infer_level_or_phase_senior():
    scraper = ObiScraper()
    nivel = scraper.infer_level_or_phase(
        url_path="fase3/programacao/",
        link_text="Programação Sênior",
        filename="senior.pdf"
    )
    assert nivel == "senior"


def test_infer_level_or_phase_fallback_to_phase():
    scraper = ObiScraper()
    nivel = scraper.infer_level_or_phase(
        url_path="fase1/programacao/cadernos/",
        link_text="Caderno de Provas",
        filename="caderno.pdf"
    )
    assert nivel == "fase1"


def test_extract_pdf_links_from_html(sample_obi_html):
    scraper = ObiScraper()
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2024/fase1/programacao/cadernos/"
    ano = 2024

    links = scraper.extract_pdf_links(sample_obi_html, page_url, ano)

    assert len(links) == 3
    # Ignorou solucao.zip
    filenames = [l.nome_arquivo for l in links]
    assert "caderno_pj.pdf" in filenames
    assert "caderno_p1.pdf" in filenames
    assert "caderno_p2.pdf" in filenames

    pj_link = next(l for l in links if l.nome_arquivo == "caderno_pj.pdf")
    assert pj_link.ano == 2024
    assert pj_link.nivel == "pj"
    assert pj_link.url == "https://olimpiada.ic.unicamp.br/passadas/OBI2024/fase1/programacao/cadernos/caderno_pj.pdf"
