"""Domain models for test cases, solutions, and question organization."""
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional
from src.core.config import OrganizeConfig


@dataclass(frozen=True)
class QuestionFolder:
    """Representa a pasta de uma questao contendo problem.json."""
    path: Path
    ano: int
    nivel: str
    titulo: str
    titulo_normalizado: str


@dataclass(frozen=True)
class TestCasePair:
    """Representa um par biunivoco consistente de entrada e saida."""
    __test__ = False
    id: int
    input_file: Path
    output_file: Path


@dataclass(frozen=True)
class TestCaseSource:
    """Representa a origem compactada de casos de teste em gabaritos/."""
    __test__ = False
    path_zip: Path
    ano: int
    nivel: str
    nome_normalizado: str



@dataclass(frozen=True)
class SolutionSource:
    """Representa um arquivo ou zip de solucao oficial em codigo/."""
    path_arquivo: Path
    ano: int
    nivel: str
    nome_normalizado: str
    linguagem: str


@dataclass
class OrganizeResult:
    """Resultado do processamento de organizacao de uma questao."""
    questao: str
    test_pairs: List[TestCasePair] = field(default_factory=list)
    solutions_count: int = 0
    status: str = "sem_recursos"
    mensagem: str = ""
