"""Unit tests for code solutions scraper in ObiScraper."""
import pytest
from src.crawler.scraper import ObiScraper, CodigoSolucao


@pytest.fixture
def scraper():
    return ObiScraper()


def test_extract_code_links_valid_languages(scraper):
    html = """
    <html>
        <body>
            <div class="problem">
                <h3>Cinema</h3>
                <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/cinema.java">Solucao Java</a>
                <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/cinema_js.js">Solucao JS</a>
                <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/cinema_py.py">Solucao Python</a>
                <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/andre.cpp">Solucao C++</a>
                <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/fonte.c">Solucao C</a>
                <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/cinema.pas">Solucao Pascal</a>
                <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/solucoes.zip">Pacote Zip</a>
            </div>
        </body>
    </html>
    """
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2022/fase1/programacao/"
    links = scraper.extract_code_links(html, page_url, ano=2022)

    assert len(links) == 7
    langs = {l.linguagem for l in links}
    assert langs == {"java", "js", "py", "cpp", "c", "pas", "zip"}

    java_link = next(l for l in links if l.linguagem == "java")
    assert java_link.nome_problema == "cinema"
    assert java_link.nivel == "pj"
    assert java_link.ano == 2022
    assert java_link.nome_arquivo == "cinema.java"
    assert java_link.url == "https://olimpiada.ic.unicamp.br/static/extras/obi2022/solucoes/2022f1pj_cinema/cinema.java"


def test_extract_code_links_py3_extension(scraper):
    html = """
    <html>
        <body>
            <a href="/static/extras/obi2016/solucoes/2016f1pj_jogo/ranido.py3">Solucao Python 3</a>
        </body>
    </html>
    """
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2016/fase1/programacao/"
    links = scraper.extract_code_links(html, page_url, ano=2016)

    assert len(links) == 1
    assert links[0].linguagem == "py"
    assert links[0].nome_problema == "jogo"
    assert links[0].nome_arquivo == "ranido.py3"


def test_extract_code_links_ignores_gabaritos_and_pdfs(scraper):
    html = """
    <html>
        <body>
            <a href="/static/extras/obi2008/gabaritos/2008f1pj_obi.zip">Gabarito Testes</a>
            <a href="/passadas/OBI2022/fase1/caderno.pdf">Caderno Prova</a>
            <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/cinema.cpp">Solucao C++</a>
            <a href="https://externo.com/teste.cpp">Link Externo</a>
        </body>
    </html>
    """
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2022/fase1/programacao/"
    links = scraper.extract_code_links(html, page_url, ano=2022)

    assert len(links) == 1
    assert links[0].nome_arquivo == "cinema.cpp"
    assert links[0].nome_problema == "cinema"


def test_extract_code_links_deduplication(scraper):
    html = """
    <html>
        <body>
            <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/andre.cpp">Solucao 1</a>
            <a href="/static/extras/obi2022/solucoes/2022f1pj_cinema/andre.cpp">Solucao 1 Repetida</a>
        </body>
    </html>
    """
    page_url = "https://olimpiada.ic.unicamp.br/passadas/OBI2022/fase1/programacao/"
    links = scraper.extract_code_links(html, page_url, ano=2022)

    assert len(links) == 1


def test_infer_problem_name_from_url(scraper):
    assert scraper.infer_problem_name("/static/extras/obi2022/solucoes/2022f1pj_cinema/andre.cpp") == "cinema"
    assert scraper.infer_problem_name("/static/extras/obi2020/solucoes/2020f2p1_lesma/lesma.c") == "lesma"
    assert scraper.infer_problem_name("/static/extras/obi2004/solucoes/2004f0p0_par/par.pas") == "par"
    assert scraper.infer_problem_name("/static/extras/obi2012/solucoes/2012f1senior_campeonato/camp.c") == "campeonato"
