# Plano de Implementacao: Exportacao do Dataset OBI Python (`dataset_obi_python`)

## 1. Contexto e Objetivo

O diretorio `output_with_code` contem a base consolidada de questoes da OBI com solucoes oficiais em multiplas linguagens (C, C++, Java, JavaScript e Python). O objetivo deste plano e implementar a extracao e geracao automatizada do diretorio `dataset_obi_python`, contendo exclusivamente as questoes que possuem codigo de solucao em Python (`.py`, `.py3`), preservando rigorosamente a mesma hierarquia (`[ano]/[nivel]/[nome_questao]`) e copiando apenas:
- `problem.json`
- Pasta `test_cases/` (com `inputs/` e `outputs/`)
- Pasta `solutions/` contendo **estritamente** os arquivos Python.

## 2. Modulos e Componentes

### 2.1 Servico de Dominio (`src/processor/python_dataset_builder.py`)
- Classe `PythonDatasetBuilder`:
  - Metodo `is_python_file(path: Path) -> bool`: verifica extensoes `.py` e `.py3`.
  - Metodo `has_python_solution(question_dir: Path) -> tuple[bool, list[Path]]`: verifica se `solutions/` contem codigos Python.
  - Metodo `export_question(source_question_dir: Path, target_question_dir: Path) -> dict`: copia `problem.json`, `test_cases/` e apenas as solucoes Python para `solutions/`.
  - Metodo `build_dataset(source_dir: Path, target_dir: Path, ano_filtro: Optional[int] = None, nivel_filtro: Optional[str] = None, force: bool = False) -> dict`: varre `source_dir`, filtra e gera o dataset em `target_dir`.

### 2.2 Integracao com a Interface CLI (`main.py`)
- Adicionar a etapa `"export-python-dataset"` ao parser de argumentos `--step`.
- Invocar `PythonDatasetBuilder` com suporte aos filtros opcionais `--ano`, `--nivel` e `--force`.

### 2.3 Suite de Testes TDD (`tests/unit/test_python_dataset_builder.py`)
- Teste de identificacao de solucoes Python (.py, .py3) vs outras linguagens (.cpp, .c, .java, .js).
- Teste de isolamento: garantia de que arquivos nao-Python nao sao copiados para a pasta `solutions/` de destino.
- Teste de exclusao: questoes sem nenhuma solucao Python nao devem ser criadas no diretorio de destino.
- Teste de integridade: `problem.json` e todos os casos de teste em `test_cases/` sao preservados.
- Teste de integracao da CLI em `tests/unit/test_cli.py`.

## 3. Checklist de Execucao

- [ ] Implementar testes unitarios em `tests/unit/test_python_dataset_builder.py`
- [ ] Implementar `PythonDatasetBuilder` em `src/processor/python_dataset_builder.py`
- [ ] Exportar `PythonDatasetBuilder` no `src/processor/__init__.py`
- [ ] Atualizar `main.py` com o step `export-python-dataset`
- [ ] Adicionar teste de CLI em `tests/unit/test_cli.py`
- [ ] Executar a geracao de `dataset_obi_python` em disco
- [ ] Validar a integridade dos dados gerados em `dataset_obi_python`
- [ ] Executar a suite completa com `uv run pytest`
- [ ] Registrar telemetria de tokens no prompt 046
