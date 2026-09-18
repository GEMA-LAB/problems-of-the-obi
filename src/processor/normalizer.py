"""Modulo de normalizacao e pareamento biunivoco de casos de teste."""
import re
import shutil
from pathlib import Path
from typing import Dict, List, Tuple
from src.core.config import EXTENSOES_ENTRADA_TESTE, EXTENSOES_SAIDA_TESTE
from src.models.test_case import TestCasePair


def natural_sort_key(string_: str) -> list:
    """Chave para ordenacao natural numerica (ex: 1, 2, 10 ao inves de 1, 10, 2)."""
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r"(\d+)", str(string_))]


class TestCaseNormalizer:
    """Descobre pares de teste nos formatos da OBI e os normaliza sequencialmente a partir de 1."""
    __test__ = False

    def __init__(self):

        self.exts_in = tuple(ext.lower() for ext in EXTENSOES_ENTRADA_TESTE)
        self.exts_out = tuple(ext.lower() for ext in EXTENSOES_SAIDA_TESTE)

    def is_input_file(self, path: Path) -> bool:
        """Determina se o arquivo e um candidato valido a entrada de teste."""
        name_lower = path.name.lower()
        if path.suffix.lower() in self.exts_in:
            return True
        if name_lower in ("in", "in.txt", "input", "input.txt"):
            return True
        if name_lower.startswith("in") and any(c.isdigit() for c in name_lower):
            return True
        return False

    def is_output_file(self, path: Path) -> bool:
        """Determina se o arquivo e um candidato valido a saida de teste."""
        name_lower = path.name.lower()
        if path.suffix.lower() in self.exts_out:
            return True
        if name_lower in ("out", "out.txt", "output", "output.txt", "sol", "sol.txt"):
            return True
        if (name_lower.startswith("out") or name_lower.startswith("sol")) and any(c.isdigit() for c in name_lower):
            return True
        return False

    def get_pairing_key(self, file_path: Path) -> str:
        """Gera uma chave normalizada para associar entrada e saida."""
        parent_part = file_path.parent.name
        stem = file_path.stem.lower()

        # Se o arquivo se chama simplesmente 'in' ou 'out', a chave e o nome da pasta pai
        if stem in ("in", "out", "sol", "input", "output"):
            return parent_part

        # Se contem digitos, extrai os digitos como chave primaria de pareamento
        digits = "".join(c for c in stem if c.isdigit())
        if digits:
            prefix = "".join(c for c in stem if not c.isdigit() and c not in ("-", "_", "."))
            # Se comeca com in ou out, normaliza o prefixo
            if prefix in ("in", "out", "sol", "input", "output"):
                return f"{parent_part}_{digits}"
            return f"{parent_part}_{prefix}_{digits}"

        return f"{parent_part}_{stem}"

    def scan_and_pair(self, raw_dir: Path) -> List[Tuple[Path, Path]]:
        """
        Varre o diretorio procurando arquivos de entrada e saida, garantindo correlacao 1-1.
        Rejeita entradas ou saidas orfas.
        """
        raw_dir = Path(raw_dir)
        if not raw_dir.exists():
            return []

        all_files = [f for f in raw_dir.rglob("*") if f.is_file()]

        inputs: Dict[str, Path] = {}
        outputs: Dict[str, Path] = {}

        # 1. Classifica os arquivos
        for file_path in all_files:
            if self.is_input_file(file_path):
                key = self.get_pairing_key(file_path)
                if key not in inputs:
                    inputs[key] = file_path
            elif self.is_output_file(file_path):
                key = self.get_pairing_key(file_path)
                if key not in outputs:
                    outputs[key] = file_path

        # 2. Pareamento por chaves identicas
        paired_keys = set(inputs.keys()) & set(outputs.keys())
        pairs: List[Tuple[Path, Path]] = []

        for key in paired_keys:
            pairs.append((inputs[key], outputs[key]))

        # 3. Fallback: se nao houve match por chave mas a quantidade de inputs e outputs for igual
        if not pairs and len(inputs) > 0 and len(inputs) == len(outputs):
            sorted_inputs = sorted(inputs.values(), key=lambda p: natural_sort_key(p.name))
            sorted_outputs = sorted(outputs.values(), key=lambda p: natural_sort_key(p.name))
            for in_f, out_f in zip(sorted_inputs, sorted_outputs):
                pairs.append((in_f, out_f))

        # Ordenacao natural final com base no caminho do arquivo de entrada
        pairs.sort(key=lambda p: natural_sort_key(str(p[0])))
        return pairs

    def normalize_to_destination(
        self,
        pairs: List[Tuple[Path, Path]],
        test_cases_dir: Path,
    ) -> List[TestCasePair]:
        """
        Organiza os pares de teste em test_cases/inputs/[id].in e test_cases/outputs/[id].out.
        Tambem disponibiliza [id].in e [id].out diretamente na raiz de test_cases/ para compatibilidade.
        """
        test_cases_dir = Path(test_cases_dir)
        inputs_dir = test_cases_dir / "inputs"
        outputs_dir = test_cases_dir / "outputs"

        inputs_dir.mkdir(parents=True, exist_ok=True)
        outputs_dir.mkdir(parents=True, exist_ok=True)

        result_pairs: List[TestCasePair] = []

        for idx, (src_in, src_out) in enumerate(pairs, start=1):
            dest_in = inputs_dir / f"{idx}.in"
            dest_out = outputs_dir / f"{idx}.out"

            # Copia para inputs/ e outputs/
            shutil.copy2(src_in, dest_in)
            shutil.copy2(src_out, dest_out)

            # Copia direta para a raiz de test_cases/
            root_in = test_cases_dir / f"{idx}.in"
            root_out = test_cases_dir / f"{idx}.out"
            shutil.copy2(src_in, root_in)
            shutil.copy2(src_out, root_out)

            result_pairs.append(
                TestCasePair(
                    id=idx,
                    input_file=dest_in,
                    output_file=dest_out,
                )
            )

        return result_pairs
