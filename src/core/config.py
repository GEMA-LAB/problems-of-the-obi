"""Core settings and constants for the OBI crawler pipeline."""
from pathlib import Path

# URLs e Endpoints
BASE_OBI_URL = "https://olimpiada.ic.unicamp.br/passadas/"

# Timeouts e Delays (em segundos)
DEFAULT_TIMEOUT = 15
DEFAULT_REQUEST_DELAY = 0.5

# Anos de cobertura das provas OBI
START_YEAR = 1999
END_YEAR = 2026

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

    # Fase 1b
    "fase1b/programacao/",
    "fase1b/programacao/cadernos/",

    # Fase 2
    "fase2/programacao/",
    "fase2/programacao/cadernos/",

    # Fase 2b
    "fase2b/programacao/",
    "fase2b/programacao/cadernos/",

    # Fase 3
    "fase3/programacao/",
    "fase3/programacao/cadernos/",

    # Fase 3b
    "fase3b/programacao/",
    "fase3b/programacao/cadernos/"
]

# Diretórios padrão do projeto
DEFAULT_CADERNOS_DIR = Path("cadernos")
DEFAULT_GABARITOS_DIR = Path("gabaritos")
DEFAULT_CODIGO_DIR = Path("codigo")
DEFAULT_OUTPUT_DIR = Path("output_question_obi")
