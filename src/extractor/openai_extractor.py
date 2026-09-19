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
            if not self.config.api_key or self.config.api_key == "placeholder_key":
                self.config = ExtractorConfig(
                    base_url=self.config.base_url,
                    api_key="provided_client",
                    model=self.config.model,
                    prompt_template_path=self.config.prompt_template_path,
                    pasta_entrada=self.config.pasta_entrada,
                    pasta_output=self.config.pasta_output,
                )
        else:
            base_url = self.config.base_url
            api_key = self.config.api_key or "placeholder_key"
            self.client = OpenAI(
                api_key=api_key,
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
        if not self.config.api_key or self.config.api_key == "placeholder_key":
            raise ValueError("OPENAI_API_KEY nao configurada no .env.")

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

    def save_problem(
        self,
        problem: ProblemSchema,
        output_base: Optional[Path] = None,
        source_pdf: Optional[Path] = None,
        base_cadernos_dir: Optional[Path] = None,
    ) -> Path:
        """
        Salva o problema em output_with_code/[ano]/[nivel]/[nome_questao]/problem.json,
        espelhando rigorosamente a estrutura de pastas do source_pdf em cadernos/.
        """
        base_dir = Path(output_base or self.config.pasta_output)
        clean_title = sanitize_filename(problem.title) or "Sem_Titulo"

        ano = str(problem.year).strip() or "unknown"
        nivel = str(problem.level).strip().lower() or "geral"

        if source_pdf is not None:
            source_path = Path(source_pdf)
            base_cadernos = Path(base_cadernos_dir or self.config.pasta_entrada)
            try:
                rel_parts = source_path.relative_to(base_cadernos).parts
            except ValueError:
                rel_parts = source_path.parts

            for part in rel_parts:
                if part.isdigit() and len(part) == 4 and 1999 <= int(part) <= 2030:
                    ano = part
                    break

            for part in rel_parts:
                part_clean = part.lower().strip()
                if part_clean in ("pj", "p0", "junior"):
                    nivel = "pj"
                    break
                elif part_clean in ("p1", "n1", "nivel1", "nivel 1"):
                    nivel = "p1"
                    break
                elif part_clean in ("p2", "n2", "nivel2", "nivel 2"):
                    nivel = "p2"
                    break
                elif part_clean in ("senior", "ps", "pu", "sen"):
                    nivel = "senior"
                    break
                elif part_clean in ("geral", "iniciacao", "cfobi"):
                    nivel = part_clean
                    break

            if nivel in ("geral", "") and len(rel_parts) >= 2:
                parent_name = source_path.parent.name.lower().strip()
                if parent_name in ("p1", "p2", "pj", "senior"):
                    nivel = parent_name

        level_map = {
            "n1": "p1", "nivel1": "p1", "p1": "p1",
            "n2": "p2", "nivel2": "p2", "p2": "p2",
            "pj": "pj", "junior": "pj", "p0": "pj",
            "senior": "senior", "ps": "senior", "pu": "senior",
            "geral": "geral",
        }
        nivel = level_map.get(nivel, nivel)

        problem.year = ano
        problem.level = nivel

        target_dir = base_dir / ano / nivel / clean_title
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
                    self.save_problem(p, output_base=output_base, source_pdf=pdf_path)
                    extracted_all.append(p)

            except Exception as e:
                logger.error(f"Erro ao processar caderno {pdf_path}")
                errors.append(pdf_path)

        return extracted_all, errors
