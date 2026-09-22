# Plano de Implementacao: Remocao de Codigo Legado Nao Utilizado

## 1. Contexto e Diagnostico

O repositorio passou por uma migracao completa para Clean Architecture, isolando as responsabilidades em modulos especializados dentro de `src/`:
- `src/core/`: Configuracoes, constantes e cliente HTTP com retry e stream.
- `src/crawler/`: Scrapers e downloaders modulares para cadernos, codigos e gabaritos.
- `src/extractor/`: Extrator de questoes via API OpenAI com Files API.
- `src/models/`: Entidades de dominio para questoes, casos de teste e solucoes.
- `src/processor/`: Extrator de zips com prevencao a Zip Slip, normalizador de casos de teste, correspondencia heuristica e saneamento de dataset.

No entanto, o arquivo `main.py` reteve o codigo monolitico original (linhas 35 a 763), consistindo em 728 linhas de funcoes legadas, globais desnecessarios e imports de dependencias nao utilizadas (`google.genai`, `OpenAI`, `BeautifulSoup`, `requests`, etc.).

## 2. Escopo e Modulos Afetados

### 2.1 Modificacoes em `main.py`
- Remover definicoes de funcoes mortas / nao referenciadas:
  - `problemas_mapeados` (set global)
  - `baixar_cadernos_pdf`
  - `create_questions` (implementacao legada com Google Gemini)
  - `create_questions_gpt` (implementacao legada OpenAI files)
  - `limpar_nome_arquivo`
  - `baixar_gabaritos`
  - `normalizar_nome`
  - `organizar_test_cases`
  - `limpar_test_cases`
  - `limpar_pastas_test_cases`
  - `remover_questoes_sem_testes`
- Remover imports nao utilizados:
  - `os`, `re`, `json`, `time`, `shutil`, `zipfile`, `unicodedata`, `requests`, `bs4.BeautifulSoup`, `urllib.parse.urljoin`, `google.genai`, `google.genai.types`, `openai.OpenAI`.
- Preservar integralmente:
  - `load_dotenv()`
  - `def main()` com toda a interface CLI (`--step`, `--ano`, `--nivel`, `--force`) e delegacoes para as classes de `src/`.
  - `if __name__ == "__main__": main()`

### 2.2 Gerenciamento de Dependencias em `pyproject.toml`
- Remover o pacote `google-genai` que era usado exclusivamente pelo metodo legado `create_questions`.
- Atualizar `uv.lock` via `uv remove google-genai`.

### 2.3 Validacao de Testes
- Executar suite automatizada completa de testes com `uv run pytest`.
- Garantir que todos os 111 testes continuem passando com 0 falhas e sem alertas de depreciacao provenientes do `google-genai`.

## 3. Checklist de Execucao

- [ ] Criar branch de refatoracao dedicada `refactor/remove-legacy-code`
- [ ] Atualizar `main.py` expurgando imports e funcoes legadas
- [ ] Remover dependencia `google-genai` com `uv remove google-genai`
- [ ] Validar execucao de todos os testes unitarios com `uv run pytest`
- [ ] Atualizar metricas no prompt 044 e gerar walkthrough
