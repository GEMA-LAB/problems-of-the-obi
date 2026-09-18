"""Modulo de extracao segura de arquivos compactados (.zip)."""
import os
import zipfile
import shutil
from pathlib import Path
from typing import List, Optional
from src.core.config import EXTENSOES_CODIGO


class ZipExtractor:
    """Extrai de forma segura e resiliente arquivos compactados de gabaritos e solucoes."""

    def __init__(self, temp_dir: Optional[Path] = None):
        self.temp_dir = Path(temp_dir) if temp_dir else None

    def extract_test_cases(self, zip_path: Path, target_dir: Path) -> bool:
        """
        Extrai todos os arquivos de um zip de gabarito para target_dir com protecao Zip Slip.
        Retorna True em caso de sucesso e False se o arquivo for invalido ou corrompido.
        """
        zip_path = Path(zip_path)
        target_dir = Path(target_dir)

        if not zip_path.exists() or not zipfile.is_zipfile(zip_path):
            return False

        target_dir.mkdir(parents=True, exist_ok=True)
        resolved_target = target_dir.resolve()

        try:
            with zipfile.ZipFile(zip_path, 'r') as zf:
                for member in zf.infolist():
                    dest_path = (target_dir / member.filename).resolve()
                    try:
                        common = os.path.commonpath([str(resolved_target), str(dest_path)])
                    except ValueError:
                        continue

                    if common != str(resolved_target):
                        continue

                    if member.is_dir():
                        dest_path.mkdir(parents=True, exist_ok=True)
                    else:
                        dest_path.parent.mkdir(parents=True, exist_ok=True)
                        with zf.open(member) as source, open(dest_path, 'wb') as target:
                            shutil.copyfileobj(source, target)
            return True
        except (zipfile.BadZipFile, Exception):
            return False

    def extract_solutions(self, zip_path: Path, target_dir: Path) -> List[Path]:
        """
        Extrai arquivos de solucao oficial contidos em um ZIP, filtrando apenas extensoes de codigo suportadas.
        """
        zip_path = Path(zip_path)
        target_dir = Path(target_dir)

        if not zip_path.exists() or not zipfile.is_zipfile(zip_path):
            return []

        target_dir.mkdir(parents=True, exist_ok=True)
        resolved_target = target_dir.resolve()
        extracted_files: List[Path] = []

        try:
            with zipfile.ZipFile(zip_path, 'r') as zf:
                for member in zf.infolist():
                    if member.is_dir():
                        continue

                    dest_path = (target_dir / member.filename).resolve()
                    try:
                        common = os.path.commonpath([str(resolved_target), str(dest_path)])
                    except ValueError:
                        continue

                    if common != str(resolved_target):
                        continue

                    ext = Path(member.filename).suffix.lower()
                    if ext not in EXTENSOES_CODIGO:
                        continue

                    dest_path.parent.mkdir(parents=True, exist_ok=True)
                    with zf.open(member) as source, open(dest_path, 'wb') as target:
                        shutil.copyfileobj(source, target)
                    extracted_files.append(dest_path)
            return extracted_files
        except (zipfile.BadZipFile, Exception):
            return []
