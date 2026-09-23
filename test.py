from pathlib import Path

path_out = Path('dataset_obi_python')

for path in path_out.glob("*"):
    if path.is_dir():
        print(path.name)