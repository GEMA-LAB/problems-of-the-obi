"""Modulo de limpeza e expurgo de residuos e questoes invalidas."""
import shutil
from pathlib import Path
from typing import List
from src.models.test_case import TestCasePair


class DatasetCleaner:
    """Higieniza o diretorio test_cases e expurga pastas de questoes sem testes validos."""

    def clean_test_cases_residuals(
        self,
        test_cases_dir: Path,
        valid_pairs: List[TestCasePair],
    ) -> None:
        """
        Remove de test_cases_dir todos os arquivos e pastas que nao sejam os pares de teste normalizados.
        """
        test_cases_dir = Path(test_cases_dir)
        if not test_cases_dir.exists():
            return

        # Arquivos esperados em inputs/ e outputs/ e na raiz de test_cases/
        expected_paths = set()
        for pair in valid_pairs:
            expected_paths.add(pair.input_file.resolve())
            expected_paths.add(pair.output_file.resolve())
            expected_paths.add((test_cases_dir / f"{pair.id}.in").resolve())
            expected_paths.add((test_cases_dir / f"{pair.id}.out").resolve())

        # Subdiretorios permitidos
        inputs_dir = (test_cases_dir / "inputs").resolve()
        outputs_dir = (test_cases_dir / "outputs").resolve()

        # 1. Varre itens diretamente na raiz de test_cases_dir
        for item in list(test_cases_dir.iterdir()):
            resolved = item.resolve()
            if item.is_dir():
                if resolved not in (inputs_dir, outputs_dir):
                    shutil.rmtree(item, ignore_errors=True)
            elif item.is_file():
                if resolved not in expected_paths:
                    item.unlink(missing_ok=True)

        # 2. Varre inputs e outputs para garantir que nada estranho sobrou
        for sub_dir in (test_cases_dir / "inputs", test_cases_dir / "outputs"):
            if sub_dir.exists():
                for item in list(sub_dir.iterdir()):
                    if item.is_dir():
                        shutil.rmtree(item, ignore_errors=True)
                    elif item.is_file() and item.resolve() not in expected_paths:
                        item.unlink(missing_ok=True)

    def validate_and_cleanup_question(
        self,
        question_path: Path,
        valid_pairs: List[TestCasePair],
    ) -> bool:
        """
        Valida se a questao possui casos de teste validos.
        Se possuir, preserva problem.json e imgs/ e retorna True.
        Se nao possuir pares validos, remove a pasta inteira da questao e retorna False.
        """
        question_path = Path(question_path)
        if not question_path.exists():
            return False

        if not valid_pairs:
            shutil.rmtree(question_path, ignore_errors=True)
            return False

        # Verifica se os arquivos de teste realmente existem em disco
        has_at_least_one_valid = any(
            pair.input_file.exists() and pair.output_file.exists()
            for pair in valid_pairs
        )

        if not has_at_least_one_valid:
            shutil.rmtree(question_path, ignore_errors=True)
            return False

        return True
