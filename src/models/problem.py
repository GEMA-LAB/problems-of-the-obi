"""Domain models for OBI problems extracted via LLM."""
from dataclasses import dataclass, field
from typing import Any, Dict, List


@dataclass
class Exemplo:
    """Exemplo de entrada e saida de um problema."""
    input: str
    output: str

    def to_dict(self) -> Dict[str, str]:
        return {
            "input": str(self.input),
            "output": str(self.output),
        }


@dataclass
class ProblemSchema:
    """
    Schema padronizado de um problema da OBI extraido via LLM.
    Limites de tempo (time_limit) e memoria (memory_limit) sao calibrados
    para a resolucao em linguagem Python. Nao possui campo difficulty.
    """
    title: str
    statement: str
    input: str
    output: str
    constraints: str
    examples: List[Exemplo]
    imgs: List[str] = field(default_factory=list)
    rating: List[int] = field(default_factory=list)
    year: str = ""
    level: str = ""
    period: str = ""
    topics: List[str] = field(default_factory=list)
    time_limit: float = 1.0
    memory_limit: int = 256

    def to_dict(self) -> Dict[str, Any]:
        """Serializa a questao em formato compativel com problem.json."""
        return {
            "title": self.title,
            "statement": self.statement,
            "input": self.input,
            "output": self.output,
            "constraints": self.constraints,
            "examples": [ex.to_dict() if isinstance(ex, Exemplo) else ex for ex in self.examples],
            "imgs": list(self.imgs),
            "rating": list(self.rating),
            "year": str(self.year),
            "level": str(self.level),
            "period": str(self.period),
            "topics": list(self.topics),
            "time_limit": float(self.time_limit),
            "memory_limit": int(self.memory_limit),
        }

    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> "ProblemSchema":
        """Cria uma instancia a partir de um dicionario, sanitizando campos e ignorando difficulty."""
        raw_examples = data.get("examples", [])
        examples: List[Exemplo] = []
        for item in raw_examples:
            if isinstance(item, dict):
                examples.append(Exemplo(input=str(item.get("input", "")), output=str(item.get("output", ""))))
            elif isinstance(item, Exemplo):
                examples.append(item)

        try:
            time_limit = float(data.get("time_limit", 1.0))
        except (ValueError, TypeError):
            time_limit = 1.0

        try:
            memory_limit = int(data.get("memory_limit", 256))
        except (ValueError, TypeError):
            memory_limit = 256

        return cls(
            title=str(data.get("title", "Sem Titulo")).strip(),
            statement=str(data.get("statement", "")),
            input=str(data.get("input", "")),
            output=str(data.get("output", "")),
            constraints=str(data.get("constraints", "")),
            examples=examples,
            imgs=list(data.get("imgs", [])),
            rating=[int(r) for r in data.get("rating", []) if isinstance(r, (int, float, str)) and str(r).isdigit()],
            year=str(data.get("year", "")),
            level=str(data.get("level", "")),
            period=str(data.get("period", "")),
            topics=[str(t) for t in data.get("topics", [])],
            time_limit=time_limit,
            memory_limit=memory_limit,
        )
