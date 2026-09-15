# Arquitetura

## Visão geral do sistema

Crie cada domínio de forma separada para que o usuário consiga executar uma etapa por vez.

Dataset OBI modalidade programação
|
├── Domínio: Pesquisa das provas no site (https://olimpiada.ic.unicamp.br/passadas/)
|   |
|   ├── Funcionalidade: navegar sobre as páginas do site pegando os cadernos de questões dos anos e salvando em cadernos/[ano]/[nível]
|   ├── Funcionalidade: navegar sobre as páginas do site pegando os gabaritos das questões e salvando em gabaritos/[ano]/[nivel]
|   ├── Funcionalidade: navegar sobre as páginas do site pegando os códigos das questões e salvando em codigo/[ano]/[nivel]
|   |
├── Domínio: Extração das questões no caderno de questões (PDF) através da chamada na API das LLMs
|   |
|   ├── Funcionalidade: navegar sobre o diretório cadernos/ enviando os PDFs através de um prompt que estará no diretório src/prompts/[nome].md retornando um JSON
|   ├── Funcionalidade: a partir do JSON criar output_question_obi/[ano]/[nivel]/[nome-questao]/problem.json
|   |
├── Domínio: Atribuindo o gabarito com a questão
|   |
|   ├── Funcionalidade: a partir do output_question_obi/[ano]/[nivel]/[nome-questao]/ deve ter um gabaritos/[ano]/[nivel]/[nome] correspondente, extraia o .zip e coloque em output_question_obi/[ano]/[nivel]/[nome-questao]/test_cases/
|   ├── Funcionalidade: normalize para que todos inputs fiquem em output_question_obi/[ano]/[nivel]/[nome-questao]/test_cases/inputs/[numero].in e os outputs em output_question_obi/[ano]/[nivel]/[nome-questao]/test_cases/inputs/[numero].out, tendo um input correspondente a um output

---

## Estrutura da arquitetura

A arquitetura adota um modelo modular orientado a domínios (Domain-Driven / Clean Architecture pragmática para pipelines de dados), garantindo separação estrita de responsabilidades, testabilidade unitária e independência de execução por etapa.

### 1. Estrutura de Diretórios do Repositório

```text
problems-of-the-obi/
├── .gemini/                           # Configurações, regras, skills e histórico do Antigravity
│   ├── GEMINI.md                      # Instrução mestre do assistente
│   ├── prompts/                       # Histórico obrigatório de prompts recebidos
│   ├── rules/                         # Regras de desenvolvimento e arquitetura
│   ├── skills/                        # Habilidades do fluxo (SDD, TDD)
│   └── specs/                         # Especificações funcionais das features
├── cadernos/                          # Cadernos de provas originais baixados (PDF)
│   └── [ano]/[nivel]/[arquivo].pdf
├── gabaritos/                         # Gabaritos e casos de teste brutos (ZIP)
│   └── [ano]/[nivel]/[arquivo].zip
├── codigo/                            # Soluções e códigos-fonte oficiais (quando disponíveis)
│   └── [ano]/[nivel]/
├── output_question_obi/               # Base de dados estruturada dos problemas da OBI
│   └── [ano]/[nivel]/[nome-questao]/
│       ├── problem.json               # Metadados, enunciado, restrições e exemplos
│       └── test_cases/                # Casos de teste descompactados e normalizados
│           └── inputs/
│               ├── [numero].in
│               └── [numero].out
├── src/                               # Código-fonte modular da aplicação
│   ├── __init__.py
│   ├── core/                          # Configurações globais, variáveis de ambiente e utilitários
│   │   ├── __init__.py
│   │   ├── config.py                  # Carregamento de variáveis de ambiente e caminhos padrão
│   │   ├── http_client.py             # Cliente HTTP padronizado (timeouts, retries e rate limiting)
│   │   └── exceptions.py              # Exceções de domínio personalizadas
│   ├── models/                        # Modelos de dados e schemas de validação
│   │   ├── __init__.py
│   │   ├── problem.py                 # Modelo Pydantic / dataclass para o problem.json
│   │   └── test_case.py               # Estrutura e metadados dos casos de teste
│   ├── crawler/                       # Domínio 1: Web Scraping do Portal da OBI
│   │   ├── __init__.py
│   │   ├── scraper.py                 # Navegação e descoberta de links no site da Unicamp
│   │   ├── cadernos_downloader.py     # Download de cadernos PDF organizados por ano/nível
│   │   ├── gabaritos_downloader.py    # Download de arquivos ZIP de gabarito por ano/nível
│   │   └── codigos_downloader.py      # Download de códigos das questões por ano/nível
│   ├── extractor/                     # Domínio 2: Extração e Estruturação de Questões via LLM
│   │   ├── __init__.py
│   │   ├── gemini_extractor.py        # Extração utilizando Google GenAI (Gemini)
│   │   ├── openai_extractor.py        # Extração alternativa via OpenAI GPT
│   │   ├── json_parser.py             # Sanitização, validação de schema e parsing do JSON
│   │   └── prompt_loader.py           # Leitor de templates de prompt em markdown
│   ├── prompts/                       # Prompts versionados para consumo pelas LLMs
│   │   └── extraction_prompt.md       # Persona, instruções e schema JSON estrito
│   ├── processor/                     # Domínio 3: Associação, Descompactação e Limpeza de Gabaritos
│   │   ├── __init__.py
│   │   ├── matcher.py                 # Normalização de nomes e correspondência problema <-> gabarito
│   │   ├── zip_extractor.py           # Descompactação segura dos casos de teste
│   │   ├── normalizer.py              # Padronização de numeração: [numero].in e [numero].out
│   │   └── cleaner.py                 # Limpeza de arquivos temporários e remoção de dados órfãos
│   └── reporter/                      # Domínio 4 (Auxiliar): Auditoria e Documentação
│       ├── __init__.py
│       ├── auditor.py                 # Verificação de integridade e consistência dos datasets
│       └── readme_generator.py        # Geração automatizada das tabelas de status no README.md
├── tests/                             # Testes automatizados (orientados por TDD)
│   ├── __init__.py
│   ├── conftest.py
│   ├── unit/                          # Testes unitários isolados por módulo
│   └── integration/                   # Testes de fluxo e integração entre etapas
├── main.py                            # Ponto de entrada e CLI para execução modular ou em pipeline
├── pyproject.toml                     # Gerenciamento de dependências via uv
└── README.md                          # Documentação e catálogo de problemas da OBI
```

### 2. Responsabilidades dos Módulos

1. **`src/core/`**:
   - Centraliza o carregamento do `.env` (`GEMINI_API`, `GEMINI_MODEL`, `GPT_API`, etc.).
   - Define constantes de diretório (`cadernos`, `gabaritos`, `codigo`, `output_question_obi`).
   - Implementa o cliente HTTP com tolerância a falhas, backoff exponencial e intervalos (`time.sleep`) para preservar o servidor da Unicamp.

2. **`src/models/`**:
   - `ProblemSchema`: valida rigorosamente os campos obrigatórios extraídos (`title`, `statement`, `input`, `output`, `constraints`, `examples`, `imgs`, `rating`, `year`, `level`, `period`, `topics`, `difficulty`).
   - Garante tipagem estática e serialização JSON consistente (`indent=4, ensure_ascii=False`).

3. **`src/crawler/`**:
   - Realiza scraping nas páginas históricas da OBI (`https://olimpiada.ic.unicamp.br/passadas/OBI{ano}/{padrao}`).
   - Segrega os downloads nas pastas correspondentes (`cadernos/[ano]/[nivel]`, `gabaritos/[ano]/[nivel]`, `codigo/[ano]/[nivel]`).
   - Implementa verificação de existência prévia para evitar downloads duplicados (idempotência).

4. **`src/extractor/`**:
   - Gerencia a comunicação com as APIs de LLM (Gemini e OpenAI) suportando envio de documentos PDF.
   - Utiliza prompts desacoplados de `src/prompts/`.
   - Limpa automaticamente arquivos carregados nas nuvens de API após a conclusão (`files.delete`).
   - Salva cada questão em `output_question_obi/[ano]/[nivel]/[nome-questao]/problem.json`, tratando colisões de nomes homônimos por ano.

5. **`src/processor/`**:
   - Realiza correspondência fonética/textual normalizada entre o título da questão e o nome do arquivo ZIP do gabarito.
   - Extrai o gabarito para `test_cases/`.
   - Padroniza os pares de teste em `test_cases/inputs/[numero].in` e `test_cases/inputs/[numero].out`.
   - Remove resíduos e pastas vazias, garantindo que apenas questões completas com casos de teste permaneçam no dataset final.

6. **`src/reporter/`**:
   - Varre `output_question_obi/` e gera relatórios em formato Markdown com o status de cada questão (Extração OK, Testes Auto/Manual/Pendente).
   - Atualiza o `README.md` principal do repositório.

### 3. Ponto de Entrada (`main.py`) e Execução Modular

O arquivo `main.py` atua como orquestrador central e interface CLI, permitindo:
- **Execução modular passo a passo:**
  - `uv run main.py --step download-cadernos`
  - `uv run main.py --step download-gabaritos`
  - `uv run main.py --step download-codigos`
  - `uv run main.py --step extract-questions`
  - `uv run main.py --step organize-testcases`
  - `uv run main.py --step update-readme`
- **Execução contínua em pipeline:**
  - `uv run main.py --all`
- **Parâmetros de escopo:**
  - Suporte a filtros opcionais por ano (`--ano 2024`) ou nível (`--nivel PJ`) para processamento sob demanda.
