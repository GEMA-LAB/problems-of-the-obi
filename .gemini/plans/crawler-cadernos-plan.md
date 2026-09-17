# PLANO DE IMPLEMENTAÇÃO: Crawler de Cadernos de Provas (PDF)

- **Identificador:** `crawler-cadernos-plan`
- **Especificação:** [`.gemini/specs/spec-crawler-cadernos.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-crawler-cadernos.md)
- **Branch de Trabalho:** `feat/crawler-cadernos` (criada a partir de `main`)
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md), [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md)

---

## 1. Visão Geral e Alinhamento com a Spec
Implementar de forma modular e testável o domínio de coleta dos cadernos de questões da OBI em formato PDF, desacoplando a lógica legada presente em `main.py` (`baixar_cadernos_pdf`). 

O novo módulo garantirá:
1. **Idempotência:** Arquivos já existentes em disco não serão baixados novamente.
2. **Organização estruturada:** Persistência em `cadernos/[ano]/[nivel]/[arquivo].pdf`.
3. **Resiliência e polidez:** Timeout estrito (15s), tratamento de quedas de conexão e intervalo mínimo configurável (0.5s) entre requisições.
4. **Execução isolada:** Invocação independente via CLI (`main.py --step download-cadernos`).

---

## 2. Dependências e Ambiente
- **Gerenciador:** `uv`
- **Dependências de Produção:** `requests>=2.31.0`, `beautifulsoup4>=4.12.0`
- **Dependências de Desenvolvimento (TDD):** `pytest>=8.0.0`, `responses>=0.25.0` (ou `unittest.mock`)
- **Comando de instalação:** `uv add beautifulsoup4` e `uv add --dev pytest responses`

---

## 3. Módulos Afetados e Novos Arquivos

```text
problems-of-the-obi/
├── src/
│   ├── core/
│   │   ├── __init__.py
│   │   ├── config.py                  # Constantes (URLs, padrões, timeouts, caminhos)
│   │   └── http_client.py             # Cliente HTTP com timeout e retry seguro
│   └── crawler/
│       ├── __init__.py
│       ├── scraper.py                 # Descoberta de links e inferência de nível/fase
│       └── cadernos_downloader.py     # Orquestrador do download idempotente
├── tests/
│   ├── __init__.py
│   ├── conftest.py                    # Fixtures e mocks de HTML/PDF
│   └── unit/
│       ├── test_http_client.py        # Testes de timeout, status e erros de conexão
│       ├── test_scraper.py            # Testes de parsing HTML e inferência de nível
│       └── test_cadernos_downloader.py# Testes de idempotência e escrita em disco
└── main.py                            # Ponto de entrada com flag --step download-cadernos
```

---

## 4. Checklist de Execução por Tasks (com Commits Atômicos)

Conforme a diretiva da skill `plans`, cada task executada deve resultar em um commit individual na branch `feat/crawler-cadernos`:

### [x] Task 1: Criação da Branch e Setup Estrutural
- Criar e mudar para a branch `feat/crawler-cadernos` a partir de `main`.
- Adicionar dependências necessárias via `uv`.
- Configurar a estrutura básica de pacotes em `src/core/`, `src/crawler/` e `tests/`.
- **Commit:** `feat(crawler): setup branch feat/crawler-cadernos and directory structure` (`a5f548c8`)

### [x] Task 2 (TDD): Core Config e HTTP Client
- Criar testes unitários em `tests/unit/test_http_client.py` validando timeouts e tratamento de falhas.
- Implementar `src/core/config.py` e `src/core/http_client.py`.
- Rodar `uv run pytest tests/unit/test_http_client.py` até aprovação total.
- **Commit:** `feat(core): implement http client and crawler configuration with tests` (`ba8776fa`)

### [x] Task 3 (TDD): Scraper de Links da OBI
- Criar testes unitários em `tests/unit/test_scraper.py` com mocks de HTML da OBI cobrindo fases normais e fases B.
- Implementar `src/crawler/scraper.py` (métodos de extração de links `.pdf` e inferência do nível/fase).
- Rodar `uv run pytest tests/unit/test_scraper.py`.
- **Commit:** `feat(crawler): implement link scraper and level inference with unit tests` (`7eccf490`)

### [x] Task 4 (TDD): Downloader Idempotente de Cadernos
- Criar testes unitários em `tests/unit/test_cadernos_downloader.py` simulando:
  - Arquivo inexistente -> download e salvamento.
  - Arquivo já existente -> skip sem requisição de streaming.
  - Erro 404 / 500 -> tratamento gracioso e log de advertência.
- Implementar `src/crawler/cadernos_downloader.py`.
- Rodar `uv run pytest tests/unit/test_cadernos_downloader.py`.
- **Commit:** `feat(crawler): implement idempotent cadernos pdf downloader with unit tests` (`25d6e038`)

### [x] Task 5: Integração no `main.py`
- Adicionar o parser de argumentos no `main.py` para suportar `uv run main.py --step download-cadernos`.
- Suporte a filtros opcionais por ano (`--ano 2024`) e nível (`--nivel pj`).
- **Commit:** `feat(cli): integrate cadernos crawler step into main.py` (`06898950`)

### [x] Task 6: Verificação Completa e Cobertura
- Executar suite completa de testes: `uv run pytest`.
- Garantir ausência de lint errors e aderência às regras do `python-developer.md` (16 testes aprovados).
- **Status:** 100% de testes unitários verdes.

### [ ] Task 7: Abertura do Pull Request
- Enviar a branch para o repositório remoto: `git push -u origin feat/crawler-cadernos`.
- Abrir o Pull Request listando todas as tarefas concluídas e vinculando a `spec-crawler-cadernos.md`.

---

## 5. Critérios de Aceite
1. Todos os cadernos PDF encontrados são salvos estritamente em `cadernos/[ano]/[nivel]/[nome].pdf`.
2. Executar o crawler duas vezes consecutivas não dispara downloads duplicados de arquivos já existentes.
3. 100% dos testes unitários passam com `uv run pytest`.
4. Nenhuma exceção não tratada interrompe o crawler durante falhas temporárias de conexão.
5. Cada task possui seu respectivo commit atômico no histórico do git.
