# Banco de Problemas OBI - Repositorio para Experimentos e Avaliacao

Este repositorio centraliza, padroniza e automatiza a extracao e organizacao dos problemas da **Olimpiada Brasileira de Informatica (OBI)** em formato JSON estruturado, vinculando casos de teste oficiais normalizados e solucoes de referencia em multiplas linguagens. O dataset destina-se a dar suporte a pesquisas em Inteligencia Artificial, avaliacao de Modelos de Linguagem (LLMs), geracao automatica de codigo e correcao programatica.

- **Fonte Oficial de Dados:** [Provas Passadas OBI - Instituto de Computacao da UNICAMP](https://olimpiada.ic.unicamp.br/passadas/)
- **Finalidade:** Benchmark cientifico reprodutivel, padronizado e auditado para problemas de programacao competitiva em lingua portuguesa.

---

## Arquitetura do Sistema e Estrutura de Diretorios

O projeto segue principios de arquitetura modular, com isolamento estrito entre etapas de coleta de dados (crawlers), processamento multimodal com LLM (extracao) e organizacao de recursos (casos de teste e codigos de solucao).

```text
problems-of-the-obi/
|-- .gemini/                           # Governanca de desenvolvimento, SDD e metricas
|   |-- GEMINI.md                      # Diretivas mestras do projeto e instrucoes de telemetria
|   |-- plans/                         # Planos tecnicos de implementacao por funcionalidade
|   |-- prompts/                       # Historico de prompts e metricas de consumo de tokens
|   |-- rules/                         # Diretrizes de arquitetura e desenvolvimento Python
|   |-- skills/                        # Habilidades de governanca (sdd, plans, tdd)
|   `-- specs/                         # Especificacoes formais baseadas em model.md
|-- cadernos/                          # Cadernos de provas originais em PDF
|   `-- [ano]/[nivel]/[arquivo].pdf
|-- codigo/                            # Solucoes oficiais disponibilizadas pela OBI
|   `-- [ano]/[nivel]/[arquivo_solucao].[ext]
|-- gabaritos/                         # Arquivos ZIP brutos contendo casos de teste da OBI
|   `-- [ano]/[nivel]/[arquivo].zip
|-- output_with_code/                  # Base de dados final consolidada e estruturada
|   `-- [ano]/[nivel]/[nome_questao]/
|       |-- problem.json               # Metadados, enunciado, limites e restricoes
|       |-- imgs/                      # Figuras e diagramas associados (se houver)
|       |-- solutions/                 # Solucoes oficiais associadas (C, C++, Java, Python, JS)
|       `-- test_cases/                # Casos de teste sequenciais 1-a-1
|           |-- inputs/
|           |   |-- 1.in
|           |   `-- [numero].in
|           `-- outputs/
|               |-- 1.out
|               `-- [numero].out
|-- src/                               # Modulos da aplicacao
|   |-- core/                          # Configuracoes globais, constantes e cliente HTTP
|   |-- crawler/                       # Scrapers e downloaders de cadernos, codigos e gabaritos
|   |-- extractor/                     # Extracao de questoes via API OpenAI com Files API
|   |-- models/                        # Modelos de dados de dominio (Pydantic / Dataclasses)
|   |-- processor/                     # Matcher heuristico, descompactacao, normalizacao e limpeza
|   `-- prompts/                       # Templates versionados de prompts de extracao
|-- tests/                             # Suite automatizada de testes unitarios e integracao
|-- main.py                            # Ponto de entrada e interface CLI unificada
|-- pyproject.toml                     # Gerenciamento de dependencias e ferramentas via uv
`-- README.md                          # Documentacao tecnica do projeto
```

---

## O Pipeline de Automacao

O pipeline de dados da OBI e composto por 5 etapas sequenciais e desacopladas:

1. **Download de Cadernos (Etapa 1):**
   - Rastreia e baixa automaticamente os cadernos de questoes em PDF das edicoes de 1999 a 2026.
   - Aplica numeracao sequencial de colisao (`[nome]-[numero].pdf`) para evitar sobrescrita entre fases distintas que compartilham o mesmo nome de arquivo.
   - Persiste os arquivos estritamente em `cadernos/[ano]/[nivel]/` com controle de idempotencia via `.manifest.json`.

2. **Download de Codigos de Solucao (Etapa 1.5):**
   - Baixa os codigos-fonte das solucoes oficiais publicadas no portal da OBI (`.c`, `.cpp`, `.py`, `.java`, `.js`, `.pas`, `.zip`).
   - Identifica automaticamente a linguagem de programacao e infere o nivel da prova a partir da URL e metadados.
   - Organiza os arquivos em `codigo/[ano]/[nivel]/`.

3. **Extracao de Questoes via LLM (Etapa 2):**
   - Envia os cadernos PDF diretamente para a API oficial da OpenAI utilizando a Files API nativa (`client.files.create(file=f, purpose="assistants")`).
   - Garante a exclusao obrigatoria do arquivo remoto dos servidores da OpenAI no bloco `finally`.
   - O prompt instrui o modelo a calibrar os limites de tempo (`time_limit`, float em segundos) e memoria (`memory_limit`, int em MB) para execucao em Python, sem avaliacoes subjetivas de dificuldade.
   - A pasta de saida espelha rigorosamente a localizacao relativa do caderno em `cadernos/` salvando em `output_with_code/[ano]/[nivel]/[nome_questao]/problem.json`.

4. **Download de Gabaritos e Testes (Etapa 3):**
   - Rastreia e faz download dos pacotes compactados (`.zip`) de casos de teste e gabaritos.
   - Organiza em `gabaritos/[ano]/[nivel]/` preservando a estrutura de arquivos.

5. **Organizacao de Questoes, Testes e Solucoes (Etapa 4):**
   - Realiza a higienizacao e saneamento de diretorios legados ou espurios.
   - Descompacta os arquivos ZIP de casos de teste em area temporaria segura.
   - Normaliza os testes em pares consistentes `[numero].in` e `[numero].out` alocados exclusivamente sob `test_cases/inputs/` e `test_cases/outputs/` (sem arquivos residuais soltos).
   - Executa correspondencia heuristica em 4 camadas entre os codigos de solucao em `codigo/[ano]/[nivel]/` e as questoes (exatidao, prefixo por separador, slug reverso e intersecao de tokens sem stopwords), aplicando desambiguacao intra-nivel por especificidade e copiando os arquivos para `solutions/`.
   - Valida a consistencia da questao e expurga pastas que nao possuam casos de teste validos.

---

## Configuracao do Ambiente

### 1. Instalacao do Gerenciador `uv`
O projeto adota o **[uv](https://github.com/astral-sh/uv)** como ferramenta padrao de gestao de ambientes virtuais e dependencias:

```bash
# Clone o repositorio
git clone https://github.com/GEMA-LAB/problems-of-the-obi.git
cd problems-of-the-obi

# Crie e ative o ambiente virtual
uv venv .venv
source .venv/bin/activate  # Linux / macOS
# ou no Windows PowerShell:
.venv\Scripts\Activate.ps1

# Sincronize as dependencias do projeto
uv sync
```

### 2. Variaveis de Ambiente (`.env`)
Copie o arquivo de exemplo e preencha suas credenciais de API:

```bash
cp .env.example .env
```

Configuracoes principais suportadas no `.env`:
```env
# Configuracoes para Extracao via OpenAI
OPENAI_BASE_URL=https://api.openai.com/v1
OPENAI_API_KEY=sua_chave_de_api_aqui
OPENAI_MODEL=gpt-4o-mini

# Configuracoes Legadas / Opcionais (Google Gemini)
GEMINI_API=sua_chave_gemini_aqui
GEMINI_MODEL=gemini-2.5-flash
```

---

## Execucao da Suite de Testes

O projeto adota a pratica de Test-Driven Development (TDD). Para rodar os 111 testes unitarios e de integracao com relatorio detalhado:

```bash
uv run pytest -v
```

Para rodar testes de modulos especificos:
```bash
# Testes do modulo extrator OpenAI
uv run pytest tests/unit/test_openai_extractor.py

# Testes de correspondencia heuristica de solucoes
uv run pytest tests/unit/test_matcher.py

# Testes do organizador de questoes e saneamento
uv run pytest tests/unit/test_questions_organizer.py tests/unit/test_cleaner.py
```

---

## Guia de Execucao do Pipeline via CLI (`main.py`)

A interface de linha de comando (`main.py`) permite executar tanto o fluxo completo quanto cada etapa isoladamente, com suporte a filtros por ano e nivel e forca de execucao.

### Opcoes Gerais do CLI

```text
Parametros aceitos:
  --step   Etapa a ser executada:
           download-cadernos   Download exclusivo de cadernos (PDFs)
           download-codigos    Download exclusivo de codigos de solucao
           download-gabaritos  Download exclusivo de gabaritos (.zip)
           extract-questions   Extracao estruturada via LLM (OpenAI)
           organize-questions  Organizacao de testes, solucoes e saneamento
           all                 Executa todas as etapas sequencialmente (padrao)
  --ano    Filtrar por ano especifico (ex: 2024, 2025)
  --nivel  Filtrar por nivel especifico (pj, p1, p2, senior, geral)
  --force  Forcar download ou reprocessamento ignorando cache/idempotencia
```

---

### Execucao Passo a Passo

#### Passo 1: Download dos Cadernos de Prova (PDFs)
Baixa todos os cadernos de provas disponiveis na OBI para a pasta `cadernos/`:

```bash
# Baixar todos os cadernos de todos os anos e niveis
uv run python main.py --step download-cadernos

# Baixar apenas os cadernos do ano 2025
uv run python main.py --step download-cadernos --ano 2025

# Baixar apenas o nivel Junior (pj) de 2024
uv run python main.py --step download-cadernos --ano 2024 --nivel pj

# Forcar download substituindo arquivos ja existentes
uv run python main.py --step download-cadernos --ano 2025 --force
```

#### Passo 2: Download dos Codigos de Solucao Oficial
Busca e baixa as solucoes oficiais em C, C++, Java, Python e JavaScript para `codigo/`:

```bash
# Baixar codigos de todas as edicoes
uv run python main.py --step download-codigos

# Baixar codigos apenas do ano 2025 nivel p1
uv run python main.py --step download-codigos --ano 2025 --nivel p1
```

#### Passo 3: Extracao Estruturada de Questoes com LLM
Envia os cadernos PDF para a API OpenAI, extraindo os problemas para `output_with_code/[ano]/[nivel]/[nome_questao]/problem.json`:

```bash
# Extrair todas as questoes de todos os PDFs disponiveis em cadernos/
uv run python main.py --step extract-questions

# Extrair apenas cadernos de 2025
uv run python main.py --step extract-questions --ano 2025

# Extrair apenas cadernos de 2025 nivel p1
uv run python main.py --step extract-questions --ano 2025 --nivel p1
```

#### Passo 4: Download dos Gabaritos e Casos de Teste (ZIPs)
Baixa os arquivos `.zip` de testes fornecidos pela OBI para `gabaritos/`:

```bash
# Baixar gabaritos de todos os anos
uv run python main.py --step download-gabaritos

# Baixar gabaritos especificos de 2025
uv run python main.py --step download-gabaritos --ano 2025
```

#### Passo 5: Organizacao de Questoes, Testes e Solucoes
Descompacta e normaliza casos de teste em `inputs/[numero].in` e `outputs/[numero].out`, associa os codigos de solucao oficiais correspondentes na subpasta `solutions/` e expurga questoes sem testes:

```bash
# Organizar todas as questoes de todos os anos
uv run python main.py --step organize-questions

# Organizar apenas o ano 2025 nivel p1
uv run python main.py --step organize-questions --ano 2025 --nivel p1

# Forcar reprocessamento e reorganizacao de testes ja existentes
uv run python main.py --step organize-questions --ano 2025 --nivel p1 --force
```

---

### Execucao Completa do Pipeline (`--step all`)

Para executar o pipeline ponta a ponta, processando sequencialmente todas as etapas:

```bash
# Execucao completa para toda a base historica (1999-2026)
uv run python main.py --step all

# Execucao completa delimitada a um ano especifico
uv run python main.py --step all --ano 2025

# Execucao completa delimitada a ano e nivel com sobrescrita forcada
uv run python main.py --step all --ano 2025 --nivel p1 --force
```

---

## Formato do `problem.json`

Cada questao extraida contem a seguinte estrutura de dados padronizada:

```json
{
    "title": "Fila",
    "statement": "Descricao completa do enunciado da questao...",
    "input": "Descricao do formato das entradas...",
    "output": "Descricao do formato das saidas esperadas...",
    "constraints": "Restricoes matematicas e limites de valores dos parametros...",
    "examples": [
        {
            "input": "4\n1 2 3 4\n",
            "output": "10\n"
        }
    ],
    "imgs": [],
    "rating": [100],
    "year": "2025",
    "level": "p1",
    "period": "Fase 1",
    "topics": ["vetores", "fila", "ordenacao"],
    "time_limit": 1.0,
    "memory_limit": 256
}
```

---

## Metodologia de Governanca (Spec-Driven Development)

O desenvolvimento deste repositorio segue o fluxo estruturado de **Spec-Driven Development (SDD)**:

1. **Especificacao Formal (`.gemini/specs/`):** Nenhuma alteracao de arquitetura ou comportamento ocorre sem uma especificacao previa seguindo `model.md` (objetivo, entidades, pre-condicoes, regras de negocio, invariantes e escopo negativo).
2. **Plano de Implementacao (`.gemini/plans/`):** Todo plano de trabalho e versionado com branch dedicada (`feat/[nome]`), commits atomicos individuais por tarefa no padrao Conventional Commits e abertura de Pull Request ao final.
3. **Desenvolvimento Orientado a Testes (`.gemini/skills/tdd`):** Testes unitarios sao escritos antes da implementacao do codigo de producao, garantindo 100% de sucesso da suite antes da conclusao.
4. **Historico e Telemetria (`.gemini/prompts/`):** Todo comando e instrucao recebida nesta conversa e persistido com telemetria exata de consumo de tokens (input, output, raciocinio, cache e contagem de chamadas).

---

## Licenca e Atribuicao Academica

O material das provas, enunciados, gabaritos e solucoes oficiais disponibilizados neste repositorio sao de titularidade e autoria da organizacao da **Olimpiada Brasileira de Informatica (OBI)** e do **Instituto de Computacao da Universidade Estadual de Campinas (UNICAMP)**. 

Este projeto e mantido estritamente para **fins educacionais, pesquisa cientifica e construcao de benchmarks para modelos de linguagem**.