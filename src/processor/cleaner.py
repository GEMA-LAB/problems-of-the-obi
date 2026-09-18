"""Modulo de limpeza e expurgo de residuos e questoes invalidas."""
import json
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

        # Arquivos esperados exclusivamente em inputs/ e outputs/
        expected_paths = set()
        for pair in valid_pairs:
            expected_paths.add(pair.input_file.resolve())
            expected_paths.add(pair.output_file.resolve())

        # Subdiretorios permitidos
        inputs_dir = (test_cases_dir / "inputs").resolve()
        outputs_dir = (test_cases_dir / "outputs").resolve()

        # 1. Varre itens diretamente na raiz de test_cases_dir: nenhum arquivo solto deve permanecer
        for item in list(test_cases_dir.iterdir()):
            resolved = item.resolve()
            if item.is_dir():
                if resolved not in (inputs_dir, outputs_dir):
                    shutil.rmtree(item, ignore_errors=True)
            elif item.is_file():
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

    def migrate_legacy_directories(
        self,
        output_dir: Path,
        cadernos_dir: Path,
    ) -> int:
        """
        Detecta e migra subdiretorios em output_dir que nao existem em cadernos_dir
        (ex: output_with_code/2025/n1) para o nivel canonico (ex: 2025/p1),
        atualizando problem.json e expurgando pastas orfas vazias.
        """
        output_dir = Path(output_dir)
        cadernos_dir = Path(cadernos_dir)
        if not output_dir.exists():
            return 0

        canonical_map = {
            "n1": "p1",
            "nivel1": "p1",
            "nivel 1": "p1",
            "n2": "p2",
            "nivel2": "p2",
            "nivel 2": "p2",
            "junior": "pj",
            "p0": "pj",
            "ps": "senior",
            "pu": "senior",
        }

        migrated_count = 0

        for year_dir in list(output_dir.iterdir()):
            if not year_dir.is_dir() or not year_dir.name.isdigit():
                continue

            ano = year_dir.name
            cadernos_ano_dir = cadernos_dir / ano

            for sub_dir in list(year_dir.iterdir()):
                if not sub_dir.is_dir():
                    continue

                sub_name = sub_dir.name.lower().strip()
                target_level = None

                if sub_name in canonical_map:
                    target_level = canonical_map[sub_name]
                elif cadernos_ano_dir.exists():
                    cadernos_levels = {
                        p.name.lower().strip() for p in cadernos_ano_dir.iterdir() if p.is_dir()
                    }
                    if sub_name not in cadernos_levels:
                        for c_lvl in cadernos_levels:
                            if canonical_map.get(c_lvl) == sub_name:
                                target_level = c_lvl
                                break

                if target_level and target_level != sub_name:
                    target_dir = year_dir / target_level
                    target_dir.mkdir(parents=True, exist_ok=True)

                    for item in list(sub_dir.iterdir()):
                        if item.is_dir():
                            dest_path = target_dir / item.name
                            if dest_path.exists():
                                for child in list(item.iterdir()):
                                    dest_child = dest_path / child.name
                                    if not dest_child.exists():
                                        shutil.move(str(child), str(dest_child))
                                shutil.rmtree(item, ignore_errors=True)
                            else:
                                shutil.move(str(item), str(dest_path))

                            prob_json = dest_path / "problem.json"
                            if prob_json.exists():
                                try:
                                    data = json.loads(prob_json.read_text(encoding="utf-8"))
                                    data["level"] = target_level
                                    prob_json.write_text(
                                        json.dumps(data, indent=4, ensure_ascii=False),
                                        encoding="utf-8",
                                    )
                                except Exception:
                                    pass

                            migrated_count += 1
                        elif item.is_file():
                            dest_file = target_dir / item.name
                            if not dest_file.exists():
                                shutil.move(str(item), str(dest_file))

                    shutil.rmtree(sub_dir, ignore_errors=True)

        return migrated_count

