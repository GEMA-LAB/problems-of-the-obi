"""Unit tests for gabaritos and test cases scraper in ObiScraper."""
import pytest
from src.crawler.scraper import ObiScraper, GabaritoZIP


@pytest.fixture
def scraper():
    return ObiScraper()


def test_extract_gabarito_links_matching_terms(scraper):
    html = """
    <html>
        <body>
            <div class="gabaritos">
                <a href="/static/extras/obi2023/gabaritos/2023f1pj_entrevistas.zip">Entrevistas de Emprego</a>
                <a href="/static/extras/obi2023/provas/testes_distancia.zip">Distancia na Vila</a>
                <a href="/static/extras/obi2023/outros/gabarito_oficial.zip"></a>
            </div>
        </body>
    </html>
    """
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2023/fase1/programacao/"
    links = scraper.extract_gabarito_links(html, page_url, ano=2023)

    assert len(links) == 3
    assert all(isinstance(l, GabaritoZIP) for l in links)

    l1 = links[0]
    assert l1.ano == 2023
    assert l1.nome_questao == "Entrevistas de Emprego"
    assert l1.url == "https://olimpiada.ic.unicamp.br/static/extras/obi2023/gabaritos/2023f1pj_entrevistas.zip"
    assert l1.nivel == "pj"

    l2 = links[1]
    assert l2.nome_questao == "Distancia na Vila"
    assert l2.url == "https://olimpiada.ic.unicamp.br/static/extras/obi2023/provas/testes_distancia.zip"

    # Fallback quando texto do link esta vazio
    l3 = links[2]
    assert l3.nome_questao == "gabarito_oficial"


def test_extract_gabarito_links_ignores_non_zips_and_non_gabaritos(scraper):
    html = """
    <html>
        <body>
            <a href="/static/extras/obi2023/cadernos/caderno_pj.pdf">Caderno PDF</a>
            <a href="/static/extras/obi2023/solucoes/2023f1pj_cinema/cinema.cpp">Solucao C++</a>
            <a href="/static/extras/obi2023/solucoes/2023f1pj_cinema/solucoes.zip">Solucoes ZIP</a>
            <a href="https://externo.com/gabarito.zip">Gabarito Externo</a>
            <a href="/static/extras/obi2023/gabaritos/gabarito_p1.zip">Gabarito Valido</a>
        </body>
    </html>
    """
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2023/fase1/programacao/"
    links = scraper.extract_gabarito_links(html, page_url, ano=2023)

    assert len(links) == 1
    assert links[0].url == "https://olimpiada.ic.unicamp.br/static/extras/obi2023/gabaritos/gabarito_p1.zip"


def test_extract_gabarito_links_deduplication(scraper):
    html = """
    <html>
        <body>
            <a href="/static/extras/obi2023/gabaritos/gabarito.zip">Gabarito</a>
            <a href="/static/extras/obi2023/gabaritos/gabarito.zip">Gabarito Repetido</a>
        </body>
    </html>
    """
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2023/fase1/programacao/"
    links = scraper.extract_gabarito_links(html, page_url, ano=2023)

    assert len(links) == 1


def test_extract_gabarito_links_level_inference(scraper):
    html = """
    <html>
        <body>
            <a href="/static/extras/obi2022/gabaritos/2022f1pj_cinema.zip">Testes Cinema Junior</a>
            <a href="/static/extras/obi2022/gabaritos/2022f1p1_chuva.zip">Testes Chuva Nivel 1</a>
            <a href="/static/extras/obi2022/gabaritos/2022f1p2_viagem.zip">Testes Viagem Nivel 2</a>
            <a href="/static/extras/obi2022/gabaritos/2022f1ps_trofeu.zip">Testes Senior</a>
        </body>
    </html>
    """
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2022/fase1/programacao/"
    links = scraper.extract_gabarito_links(html, page_url, ano=2022)

    assert len(links) == 4
    niveis = {l.nome_questao: l.nivel for l in links}
    assert niveis["Testes Cinema Junior"] == "pj"
    assert niveis["Testes Chuva Nivel 1"] == "p1"
    assert niveis["Testes Viagem Nivel 2"] == "p2"
    assert niveis["Testes Senior"] == "senior"
