"""Tests for PromptLoader and extraction prompt template."""
from pathlib import Path
import pytest
from src.extractor.prompt_loader import PromptLoader


def test_load_default_prompt():
    """Validates loading the official extraction prompt template."""
    loader = PromptLoader()
    prompt = loader.load_prompt()

    assert isinstance(prompt, str)
    assert len(prompt) > 100
    assert "PERSONA" in prompt
    assert "TASK" in prompt
    assert "RESTRIÇÕES" in prompt
    assert "TEMPLATE ESPERADO" in prompt

    # Mandatory constraints from specification
    assert "time_limit" in prompt
    assert "memory_limit" in prompt
    assert "Python" in prompt or "python" in prompt
    assert "difficulty" not in prompt


def test_load_custom_prompt(tmp_path):
    """Validates loading a prompt template from a custom path."""
    custom_file = tmp_path / "custom_prompt.md"
    custom_content = "Custom extraction template for OBI without difficulty."
    custom_file.write_text(custom_content, encoding="utf-8")

    loader = PromptLoader(template_path=custom_file)
    loaded = loader.load_prompt()
    assert loaded == custom_content


def test_load_nonexistent_prompt_raises():
    """Validates error handling when template file does not exist."""
    loader = PromptLoader(template_path=Path("non_existent_prompt_12345.md"))
    with pytest.raises(FileNotFoundError):
        loader.load_prompt()
