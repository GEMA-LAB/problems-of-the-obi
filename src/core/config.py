"""Core settings and constants for the OBI crawler pipeline."""
from pathlib import Path
from typing import Optional

# URLs e Endpoints
BASE_OBI_URL = "https://olimpiada.ic.unicamp.br/passadas/"

# Timeouts e Delays (em segundos)
DEFAULT_TIMEOUT = 15
DEFAULT_REQUEST_DELAY = 0.5

# Anos de cobertura das provas OBI
START_YEAR = 1999
END_YEAR = 2027

# Padrões de URL para busca de cadernos de questões (PDFs)
PADROES_CADERNOS = [
    # Nível Raiz / Geral
    "programacao/",
    "programacao/cadernos/",

    # Fase 1
    "fase1/programacao/",
    "fase1/programacao/cadernos/",
    "fase1/programacao-a/",
    "fase1/programacao-b/",
    "fase1/programacaob/",
    "fase1/programacaob/cadernos/",

    # Fase 1b
    "fase1b/programacao/",
    "fase1b/programacao/cadernos/",

    # Fase 2
    "fase2/programacao/",
    "fase2/programacao/cadernos/",
    "fase2/programacao-a/",
    "fase2/programacao-b/",
    "fase2/programacaob/",
    "fase2/programacaob/cadernos/",

    # Fase 2b
    "fase2b/programacao/",
    "fase2b/programacao/cadernos/",

    # Fase 3
    "fase3/programacao/",
    "fase3/programacao/cadernos/",
    "fase3/programacao-a/",
    "fase3/programacao-b/",
    "fase3/programacaob/",
    "fase3/programacaob/cadernos/",

    # Fase 3b
    "fase3b/programacao/",
    "fase3b/programacao/cadernos/",

    # CFOBI (Competição Feminina da OBI)
    "cfobi/programacao/",
    "cfobi/programacao/cadernos/",
]

# Diretórios padrão do projeto
DEFAULT_CADERNOS_DIR = Path("cadernos")
DEFAULT_GABARITOS_DIR = Path("gabaritos")
DEFAULT_CODIGO_DIR = Path("codigo")
DEFAULT_OUTPUT_DIR = Path("output_with_code")
DEFAULT_OPENAI_BASE_URL = "https://api.openai.com/v1"
DEFAULT_OPENAI_MODEL = "gpt-4o-mini"
DEFAULT_PROMPT_TEMPLATE = Path("src/prompts/extraction_prompt.md")

# Extensoes e mapeamentos para codigos e solucoes oficiais
EXTENSOES_CODIGO = (
    ".c",
    ".cpp",
    ".cc",
    ".cxx",
    ".py",
    ".py3",
    ".java",
    ".pas",
    ".js",
    ".zip",
)

MAPEAMENTO_LINGUAGEM = {
    ".c": "c",
    ".cpp": "cpp",
    ".cc": "cpp",
    ".cxx": "cpp",
    ".py": "py",
    ".py3": "py",
    ".java": "java",
    ".pas": "pas",
    ".js": "js",
    ".zip": "zip",
}


class CodigoCrawlerConfig:
    """Configuracao do crawler de codigos de solucao."""

    def __init__(
        self,
        pasta_base: Path = DEFAULT_CODIGO_DIR,
        timeout: int = DEFAULT_TIMEOUT,
        delay_requests: float = DEFAULT_REQUEST_DELAY,
        extensoes_validas: tuple[str, ...] = EXTENSOES_CODIGO,
    ):
        self.pasta_base = Path(pasta_base)
        self.timeout = timeout
        self.delay_requests = delay_requests
        self.extensoes_validas = extensoes_validas


# Termos para filtro de links de gabarito e casos de teste
TERMOS_GABARITO = ("gabarito", "testes")


class GabaritoCrawlerConfig:
    """Configuracao do crawler de gabaritos e casos de teste (.zip)."""

    def __init__(
        self,
        pasta_base: Path = DEFAULT_GABARITOS_DIR,
        timeout: int = DEFAULT_TIMEOUT,
        delay_requests: float = DEFAULT_REQUEST_DELAY,
        termos_filtro: tuple[str, ...] = TERMOS_GABARITO,
    ):
        self.pasta_base = Path(pasta_base)
        self.timeout = timeout
        self.delay_requests = delay_requests
        self.termos_filtro = termos_filtro


class ExtractorConfig:
    """Configuracao do extrator LLM de questoes."""

    def __init__(
        self,
        base_url: Optional[str] = None,
        api_key: Optional[str] = None,
        model: str = DEFAULT_OPENAI_MODEL,
        prompt_template_path: Path = DEFAULT_PROMPT_TEMPLATE,
        pasta_entrada: Path = DEFAULT_CADERNOS_DIR,
        pasta_output: Path = DEFAULT_OUTPUT_DIR,
    ):
        self.base_url = base_url
        self.api_key = api_key
        self.model = model
        self.prompt_template_path = Path(prompt_template_path)
        self.pasta_entrada = Path(pasta_entrada)
        self.pasta_output = Path(pasta_output)


# Constantes de organizacao de casos de teste e solucoes
DEFAULT_TEST_CASES_DIR = Path("test_cases")
DEFAULT_SOLUTIONS_DIR = Path("solutions")
DEFAULT_INPUTS_DIR = Path("inputs")
DEFAULT_OUTPUTS_DIR = Path("outputs")
EXTENSOES_ENTRADA_TESTE = (".in", ".input")
EXTENSOES_SAIDA_TESTE = (".out", ".output", ".sol")


class OrganizeConfig:
    """Configuracao para organizacao e correspondencia de questoes e recursos."""

    def __init__(
        self,
        pasta_output: Path = DEFAULT_OUTPUT_DIR,
        pasta_gabaritos: Path = DEFAULT_GABARITOS_DIR,
        pasta_codigo: Path = DEFAULT_CODIGO_DIR,
        force: bool = False,
    ):
        self.pasta_output = Path(pasta_output)
        self.pasta_gabaritos = Path(pasta_gabaritos)
        self.pasta_codigo = Path(pasta_codigo)
        self.force = force



