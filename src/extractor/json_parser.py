"""JSON sanitization and parsing utilities for LLM responses."""
import json
import logging
import re
from typing import List
from src.models.problem import ProblemSchema

logger = logging.getLogger(__name__)


def sanitize_json_markdown(raw_text: str) -> str:
    """
    Remove blocos de markdown (```json ... ``` ou ``` ... ```) e textos
    perifericos inseridos antes ou depois do JSON pela LLM.
    """
    text = raw_text.strip()
    if not text:
        return ""

    # Se contiver fences de markdown, remove o bloco externo
    if "```" in text:
        match = re.search(r"```(?:json)?\s*([\s\S]*?)\s*```", text)
        if match:
            text = match.group(1).strip()
        else:
            if text.startswith("```"):
                text = text.split("\n", 1)[-1]
            if text.endswith("```"):
                text = text.rsplit("```", 1)[0]
            text = text.strip()

    # Se ainda tiver texto antes do primeiro '[' ou '{', busca o bloco JSON
    if not (text.startswith("[") or text.startswith("{")):
        start_bracket = text.find("[")
        start_brace = text.find("{")

        if start_bracket != -1 and (start_brace == -1 or start_bracket < start_brace):
            end_bracket = text.rfind("]")
            if end_bracket != -1 and end_bracket > start_bracket:
                text = text[start_bracket : end_bracket + 1].strip()
        elif start_brace != -1:
            end_brace = text.rfind("}")
            if end_brace != -1 and end_brace > start_brace:
                text = text[start_brace : end_brace + 1].strip()

    return text


def parse_problems_json(raw_text: str) -> List[ProblemSchema]:
    """
    Sanitiza e desserializa a resposta textual da LLM em uma lista de ProblemSchema.
    Retorna lista vazia em caso de falha de decodificacao sintatica.
    """
    sanitized = sanitize_json_markdown(raw_text)
    if not sanitized:
        return []

    try:
        data = json.loads(sanitized)
    except json.JSONDecodeError as e:
        logger.warning(f"Erro ao decodificar JSON da LLM: {e}")
        return []

    if isinstance(data, dict):
        data = [data]

    if not isinstance(data, list):
        logger.warning("Resposta da LLM nao e uma lista de problemas nem um objeto JSON.")
        return []

    problems: List[ProblemSchema] = []
    for item in data:
        if isinstance(item, dict):
            try:
                problem = ProblemSchema.from_dict(item)
                problems.append(problem)
            except Exception as e:
                logger.warning(f"Erro ao converter objeto para ProblemSchema: {e}")

    return problems
