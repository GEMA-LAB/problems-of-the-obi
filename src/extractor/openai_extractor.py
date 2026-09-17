"""OpenAI-based PDF question extractor for OBI exams."""
import json
import logging
import os
import re
from pathlib import Path
from typing import List, Optional, Tuple
from openai import OpenAI

from src.core.config import (
    ExtractorConfig,
    DEFAULT_OPENAI_BASE_URL,
    DEFAULT_OPENAI_MODEL,
)
from src.extractor.prompt_loader import PromptLoader
from src.extractor.json_parser import parse_problems_json
from src.models.problem import ProblemSchema

logger = logging.getLogger(__name__)


def sanitize_filename(name: str) -> str:
    """Sanitiza nomes para criacao segura de diretorios."""
    clean = re.sub(r'[\\/*?:"<>|]', "", name)
    return clean.strip()


class OpenAiExtractor:
    """Orquestrador de extracao de questoes via API OpenAI."""

    def __init__(
        self,
        config: Optional[ExtractorConfig] = None,
        client: Optional[OpenAI] = None,
        prompt_template: Optional[str] = None,
    ):
        self.config = config or ExtractorConfig(
            base_url=os.getenv("OPENAI_BASE_URL") or DEFAULT_OPENAI_BASE_URL,
            api_key=os.getenv("OPENAI_API_KEY") or os.getenv("GPT_API"),
            model=os.getenv("OPENAI_MODEL") or os.getenv("GPT_MODEL") or DEFAULT_OPENAI_MODEL,
        )

        if client is not None:
            self.client = client
        else:
            base_url = self.config.base_url
            self.client = OpenAI(
                api_key=self.config.api_key,
                base_url=base_url if base_url else None,
            )

        self.model = self.config.model
        if prompt_template is not None:
            self.prompt_template = prompt_template
        else:
            loader = PromptLoader(self.config.prompt_template_path)
            self.prompt_template = loader.load_prompt()

    def extract_from_pdf(self, pdf_path: Path) -> List[ProblemSchema]:
        """
        Envia PDF para OpenAI Files API, chama o modelo com o prompt de extracao
        e garante a delecao do arquivo remoto no bloco finally.
        """
        pdf_file = Path(pdf_path)
        if not pdf_file.exists():
            raise FileNotFoundError(f"Arquivo PDF nao encontrado: {pdf_file}")

        logger.info(f"Fazendo upload do PDF para a API OpenAI: {pdf_file.name}")
        uploaded_file = None
        try:
            with open(pdf_file, "rb") as f:
                uploaded_file = self.client.files.create(file=f, purpose="assistants")

            logger.info(f"Processando documento {pdf_file.name} com modelo {self.model}...")
            response = self.client.responses.create(
                model=self.model,
                input=[
                    {
                        "role": "user",
                        "content": [
                            {
                                "type": "input_file",
                                "file_id": uploaded_file.id,
                            },
                            {
                                "type": "input_text",
                                "text": self.prompt_template,
                            },
                        ],
                    }
                ],
            )

            raw_text = getattr(response, "output_text", "")
            if not raw_text and hasattr(response, "choices") and response.choices:
                raw_text = response.choices[0].message.content or ""

            problems = parse_problems_json(raw_text)
            logger.info(f"Extraidos {len(problems)} problemas de {pdf_file.name}")
            return problems

        finally:
            if uploaded_file and hasattr(uploaded_file, "id"):
                try:
                    self.client.files.delete(uploaded_file.id)
                    logger.info(f"Arquivo remoto {uploaded_file.id} deletado com sucesso da OpenAI.")
                except Exception as e:
                    logger.warning(f"Falha ao deletar arquivo remoto {uploaded_file.id}: {e}")

    def save_problem(self, problem: ProblemSchema, output_base: Optional[Path] = None) -> Path:
        """
        Salva o problema em output/[titulo]/problem.json.
        Se ja existir uma pasta para o titulo com ano divergente, salva em output/[titulo]_[ano]/problem.json.
        """
        base_dir = Path(output_base or self.config.pasta_output)
        clean_title = sanitize_filename(problem.title) or "Sem_Titulo"
        ano = str(problem.year).strip() or "Unknown"

        target_dir = base_dir / clean_title
        if target_dir.exists():
            existing_problem_file = target_dir / "problem.json"
            if existing_problem_file.exists():
                try:
                    with open(existing_problem_file, "r", encoding="utf-8") as f:
                        data = json.load(f)
                    if str(data.get("year")) != ano:
                        target_dir = base_dir / f"{clean_title}_{ano}"
                except (json.JSONDecodeError, OSError):
                    pass

        target_dir.mkdir(parents=True, exist_ok=True)
        file_path = target_dir / "problem.json"
        with open(file_path, "w", encoding="utf-8") as f:
            json.dump(problem.to_dict(), f, indent=4, ensure_ascii=False)

        logger.info(f"Problema salvo com sucesso em: {file_path}")
        return file_path

    def process_cadernos(
        self,
        cadernos_paths: List[Path],
        output_base: Optional[Path] = None,
    ) -> Tuple[List[ProblemSchema], List[Path]]:
        """
        Processa uma lista de cadernos PDF, salvando cada problema e coletando falhas.
        Retorna (problemas_extraidos, lista_de_erros).
        """
        extracted_all: List[ProblemSchema] = []
        errors: List[Path] = []

        for pdf_path in cadernos_paths:
            try:
                problems = self.extract_from_pdf(pdf_path)
                if not problems:
                    errors.append(pdf_path)
                    continue

                for p in problems:
                    self.save_problem(p, output_base=output_base)
                    extracted_all.append(p)

            except Exception as e:
                logger.error(f"Erro ao processar caderno {pdf_path}: {e}")
                errors.append(pdf_path)

        return extracted_all, errors
