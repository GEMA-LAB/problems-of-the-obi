"""Loader for extraction prompt template."""
from pathlib import Path
from typing import Optional
from src.core.config import DEFAULT_PROMPT_TEMPLATE


class PromptLoader:
    """Carrega templates de prompt para envio a LLM."""

    def __init__(self, template_path: Optional[Path] = None):
        self.template_path = Path(template_path or DEFAULT_PROMPT_TEMPLATE)

    def load_prompt(self) -> str:
        """Le o conteudo do template de prompt em disco."""
        if not self.template_path.exists():
            raise FileNotFoundError(f"Arquivo de prompt nao encontrado: {self.template_path}")
        return self.template_path.read_text(encoding="utf-8").strip()
