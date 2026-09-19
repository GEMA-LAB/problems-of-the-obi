# Prompt 044 - Remocao de Codigo Legado Nao Utilizado

- **Data e Hora:** 2026-09-18 23:13:23 -03:00
- **Usuario:** Victo

## Conteudo do Prompt

```text
remova o código legado que não está sendo utilizado
```

---

## Alinhamento e Diagnostico Tecnico

1. **Contexto e Analise de Codigo Legado:**
   - O projeto foi migrado e modularizado em componentes desacoplados sob o diretorio `src/` (`src.crawler`, `src.extractor`, `src.processor`, `src.models`, `src.core`).
   - No arquivo `main.py`, foram mantidas mais de 720 linhas de funcoes monoliticas pre-refatoracao que nao sao mais invocadas pela funcao `main()` nem importadas por nenhum teste ou modulo externo.
   - Foram identificadas funcoes legadas em `main.py`:
     - `problemas_mapeados = set()`
     - `baixar_cadernos_pdf()` (linhas 42 a 142) - substituido por `CadernosDownloader`
     - `create_questions(pdfs_path)` (linhas 148 a 243) - extrator legado Gemini
     - `create_questions_gpt(pdfs_path)` (linhas 245 a 358) - extrator legado monolitico OpenAI, substituido por `OpenAiExtractor`
     - `limpar_nome_arquivo(nome)` (linhas 365 a 371) - substituido por normalizacao em `src.processor.matcher` / `normalizer`
     - `baixar_gabaritos()` (linhas 373 a 500) - substituido por `GabaritosDownloader`
     - `normalizar_nome(nome)` (linhas 505 a 509) - substituido por `normalize_name` em `src.processor.matcher`
     - `organizar_test_cases()` (linhas 511 a 563) - substituido por `QuestionsOrganizer`
     - `limpar_test_cases()` (linhas 569 a 597) - substituido por `DatasetCleaner`
     - `limpar_pastas_test_cases()` (linhas 598 a 719) - substituido por `TestCaseNormalizer` e `DatasetCleaner`
     - `remover_questoes_sem_testes()` (linhas 725 a 762) - substituido pelo pipeline de organizacao e saneamento
   - Identificados imports nao utilizados em `main.py`:
     - `os`, `re`, `json`, `time`, `shutil`, `zipfile`, `unicodedata`, `requests`, `BeautifulSoup`, `urljoin`, `google.genai`, `types`, `OpenAI`.
   - Identificada dependencia legada `google-genai` em `pyproject.toml`, utilizada exclusivamente pelo codigo legado Gemini em `main.py`, que gerava alerta de depreciacao no Python 3.14.

2. **Escopo de Acoes:**
   - Limpeza integral de `main.py`, mantendo apenas o orquestrador CLI `main()` e os imports necessarios dos modulos de `src/`.
   - Remocao da dependencia `google-genai` do ambiente via `uv remove google-genai`.
   - Execucao da suite de testes automatizados com `uv run pytest` para garantir 100% de integridade e regressao zero.

---

## Consumo de Tokens (Execucao do Prompt)

| Metrica | Quantidade |
| :--- | :--- |
| **Tokens de Entrada (sem cache)** | 1.272.091 |
| **Tokens de Entrada (com cache)** | 9.031.975 |
| **Total de Entrada** | 10.304.066 |
| **Tokens de Saida (raciocinio/thinking)** | 22.325 |
| **Tokens de Saida (resposta)** | 21.127 |
| **Total Geral de Saida** | 43.452 |
| **Total Geral Consumido** | 10.347.518 |
| **Iteracoes de Execucao** | 111 |

---

## Resultados da Implementacao

1. **Expurgo de Codigo Legado em `main.py`:**
   - Removidas 753 linhas de codigo monolitico morto e variaveis globais sem uso (`problemas_mapeados`).
   - Removidas 10 funcoes monoliticas obsoletas (`baixar_cadernos_pdf`, `create_questions`, `create_questions_gpt`, `limpar_nome_arquivo`, `baixar_gabaritos`, `normalizar_nome`, `organizar_test_cases`, `limpar_test_cases`, `limpar_pastas_test_cases`, `remover_questoes_sem_testes`).
   - Removidos 13 imports nao utilizados (`os`, `re`, `json`, `time`, `shutil`, `zipfile`, `unicodedata`, `requests`, `BeautifulSoup`, `urljoin`, `google.genai`, `types`, `OpenAI`).
   - `main.py` mantido exclusivamente como orquestrador CLI de alto nivel invocando as classes desacopladas de `src/`.

2. **Remocao da Dependencia `google-genai`:**
   - Executado `uv remove google-genai`, expurgando a biblioteca e 11 subdependencias transitivas obsoletas.
   - Atualizados `pyproject.toml` e `uv.lock`.
   - Eliminado o aviso `DeprecationWarning: '_UnionGenericAlias'` durante os testes no Python 3.14.

3. **Validacao e Integridade:**
   - Teste manual da CLI `uv run python main.py --help` executado com sucesso.
   - Suite completa de 111 testes automatizados em `uv run pytest` executada com 100% de sucesso e zero advertencias.
   - Commits atomicos organizados na branch `refactor/remove-legacy-code`.

