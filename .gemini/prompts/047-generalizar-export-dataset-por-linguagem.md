# Prompt 047 - Generalizacao do Exportador de Dataset por Linguagem de Programacao

- **Data e Hora:** 2026-09-19 11:59:40 -03:00
- **Usuario:** Victo

## Conteudo do Prompt

```text
Gostei do que você fez só que em vez de fazer uv run python main.py --step export-python-dataset, poderia ser uv run python main.py --step export-dataset --python e normalizando para construir sempre para informando as linguagens como c++ (os arquivos tem expesão .cc e .cpp), java, pascal, javascript, python. Assim, podendo construir com base na solução que queria
```

---

## Alinhamento e Diagnostico Tecnico

1. **Objetivo:**
   - Evoluir o exportador de datasets para suportar construcao parametrizada por linguagem de programacao (`python`, `c++`/`cpp`, `java`, `pascal`, `javascript`/`js`, `c`).
   - Substituir a etapa monolitica `--step export-python-dataset` pela etapa generalizada `--step export-dataset`.
   - Permitir a selecao da linguagem via argumento ou flags dedicadas (ex: `--python`, `--cpp`, `--c++`, `--java`, `--pascal`, `--javascript`, `--js`, ou `--lang [linguagem]`), mantendo compatibilidade com o formato solicitado:
     `uv run python main.py --step export-dataset --python`
   - Normalizar as extensoes suportadas por linguagem:
     - Python: `.py`, `.py3` -> Diretorio: `dataset_obi_python/`
     - C++: `.cpp`, `.cc`, `.cxx` -> Diretorio: `dataset_obi_cpp/`
     - C: `.c` -> Diretorio: `dataset_obi_c/`
     - Java: `.java` -> Diretorio: `dataset_obi_java/`
     - Pascal: `.pas` -> Diretorio: `dataset_obi_pascal/`
     - JavaScript: `.js` -> Diretorio: `dataset_obi_javascript/`
   - Garantir que cada dataset derivado contenha rigorosamente apenas as questoes que possuem solucao na linguagem solicitada, copiando `problem.json`, `test_cases/` e apenas as solucoes da linguagem especificada em `solutions/`.

2. **Arquitetura e Boas Praticas:**
   - Generalizar `PythonDatasetBuilder` para `LanguageDatasetBuilder` em `src/processor/language_dataset_builder.py` (preservando `PythonDatasetBuilder` como alias/subclasse para retrocompatibilidade).
   - Mapear dicionario canonico de linguagens e extensoes suportadas.
   - Atualizar `src/processor/__init__.py`, `src/core/config.py` e `main.py`.
   - Manter retrocompatibilidade com `--step export-python-dataset`.
   - Adicionar suite completa de testes em `tests/unit/test_language_dataset_builder.py` e atualizar `tests/unit/test_cli.py`.

3. **Criterios de Aceite:**
   - `uv run python main.py --step export-dataset --python` funciona gerando `dataset_obi_python/`.
   - `uv run python main.py --step export-dataset --lang cpp` (ou `--cpp`/`--c++`) funciona gerando `dataset_obi_cpp/`.
   - 100% dos testes passando com `uv run pytest`.

---

## Consumo de Tokens (Execucao do Prompt)

| Metrica | Quantidade |
| :--- | :--- |
| **Tokens de Entrada (sem cache)** | 163.761 |
| **Tokens de Entrada (com cache)** | 5.285.005 |
| **Total de Entrada** | 5.448.766 |
| **Tokens de Saida (raciocinio/thinking)** | 18.087 |
| **Tokens de Saida (resposta)** | 8.053 |
| **Total Geral de Saida** | 26.140 |
| **Total Geral Consumido** | 5.474.906 |
| **Iteracoes de Execucao** | 42 |

---

## Resultados da Implementacao

1. **`LanguageDatasetBuilder` implementado:**
   - Criada a classe `LanguageDatasetBuilder` em `src/processor/language_dataset_builder.py` com suporte parametrizado a linguagens (`python`, `cpp`, `c`, `java`, `pascal`, `javascript`).
   - Normalizacao de aliases (`c++` -> `cpp`, `js` -> `javascript`).
   - Mapeamento de extensoes e diretorios de saida padrao (`dataset_obi_[linguagem]`).
   - Copia de solucoes exclusivas da linguagem informada, `test_cases/` e `problem.json`.

2. **Retrocompatibilidade com `PythonDatasetBuilder`:**
   - `PythonDatasetBuilder` mantido como subclasse especializada de `LanguageDatasetBuilder` em `src/processor/python_dataset_builder.py`.
   - Exportacao garantida em `src/processor/__init__.py`.

3. **CLI atualizada em `main.py`:**
   - Adicionada a etapa `--step export-dataset` com flags dedicadas: `--python`, `--cpp`, `--c++`, `--java`, `--pascal`, `--javascript`, `--js`, `--c` e `--lang`/`--language`.
   - Mantida retrocompatibilidade com `--step export-python-dataset`.

4. **Testes Unitarios e Regressao:**
   - 125 testes executados com 100% de sucesso (`uv run pytest`), cobrindo novos fluxos e backward-compatibility.
