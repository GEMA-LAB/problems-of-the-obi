# Plano de Implementacao: Generalizacao do Exportador de Dataset por Linguagem (`export-dataset`)

## 1. Contexto e Objetivo

Atualmente, o pipeline possui a etapa `--step export-python-dataset` restrita a Python. O objetivo deste plano e generalizar a funcionalidade para `--step export-dataset`, permitindo a construcao de datasets especializados para qualquer linguagem suportada pela OBI:
- Python (`.py`, `.py3`) -> `dataset_obi_python`
- C++ (`.cpp`, `.cc`, `.cxx`) -> `dataset_obi_cpp`
- C (`.c`) -> `dataset_obi_c`
- Java (`.java`) -> `dataset_obi_java`
- Pascal (`.pas`) -> `dataset_obi_pascal`
- JavaScript (`.js`) -> `dataset_obi_javascript`

A chamada CLI solicitada pelo usuario:
```bash
uv run python main.py --step export-dataset --python
```
deve ser suportada diretamente, bem como opcoes equivalentes como `--cpp`, `--java`, `--pascal`, `--javascript`, `--c` ou `--lang [linguagem]`.

## 2. Modulos e Componentes

### 2.1 Servico de Dominio (`src/processor/language_dataset_builder.py`)
- Classe `LanguageDatasetBuilder`:
  - Dicionario canonico `SUPPORTED_LANGUAGES` mapeando extensoes e diretorios padrao.
  - Metodo `normalize_language(lang: str) -> str`: converte aliases (ex: `c++` -> `cpp`, `py` -> `python`, `js` -> `javascript`).
  - Metodo `is_language_file(path: Path, lang: str) -> bool`.
  - Metodo `has_language_solution(question_dir: Path, lang: str) -> tuple[bool, list[Path]]`.
  - Metodo `export_question(source_question_dir: Path, target_question_dir: Path, lang: str) -> dict`.
  - Metodo `build_dataset(source_dir: Path, target_dir: Optional[Path] = None, language: str = "python", ano_filtro: Optional[int] = None, nivel_filtro: Optional[str] = None, force: bool = False) -> dict`.
- Subclasse / retrocompatibilidade: `PythonDatasetBuilder` herdando de `LanguageDatasetBuilder` com linguagem fixada em `"python"`.

### 2.2 Integracao CLI (`main.py`)
- Atualizar `--step` para incluir `export-dataset` (mantendo `export-python-dataset` como alias).
- Adicionar flags de conveniencia na CLI:
  - `--python`: seleciona linguagem Python (padrao)
  - `--cpp`: seleciona C++ (extensoes `.cpp`, `.cc`, `.cxx`)
  - `--c`: seleciona C (`.c`)
  - `--java`: seleciona Java (`.java`)
  - `--pascal`: seleciona Pascal (`.pas`)
  - `--javascript` / `--js`: seleciona JavaScript (`.js`)
  - `--lang` / `--language`: parametro com string/choice de linguagem.

### 2.3 Suite de Testes TDD (`tests/unit/test_language_dataset_builder.py`)
- Testes para todas as linguagens suportadas e seus aliases.
- Teste garantindo que apenas arquivos da linguagem selecionada sejam copiados.
- Testes de integracao CLI em `tests/unit/test_cli.py`.

## 3. Checklist de Execucao

- [ ] Implementar `LanguageDatasetBuilder` em `src/processor/language_dataset_builder.py`
- [ ] Atualizar `src/processor/python_dataset_builder.py` e `src/processor/__init__.py`
- [ ] Implementar testes unitarios em `tests/unit/test_language_dataset_builder.py`
- [ ] Atualizar `main.py` com o step `export-dataset` e flags de linguagem
- [ ] Atualizar testes de CLI em `tests/unit/test_cli.py`
- [ ] Executar suite de testes com `uv run pytest`
- [ ] Validar execucao manual `uv run python main.py --step export-dataset --python`
- [ ] Atualizar prompt 047 e walkthrough.md
