# Banco de Problemas OBI — Repositorio para Experimentos e Avaliacao

Este repositorio centraliza, padroniza e disponibiliza problemas da **Olimpiada Brasileira de Informatica (OBI)** em formato estruturado (`JSON`), associando casos de teste padronizados para suportar experimentos em avaliacao de Modelos de Linguagem (LLMs), sistemas de correcao automatica e pesquisa em inteligencia artificial aplicada a programacao competitiva.

- **Fonte de dados oficial:** [Provas Passadas OBI - Unicamp](https://olimpiada.ic.unicamp.br/passadas/)
- **Objetivo Cientifico:** Criacao de um benchmark reprodutivel, testavel e anotado para avaliar o raciocinio logico e algoritmico de LLMs em lingua portuguesa.

---

## Arquitetura e Engenharia de Software

O projeto adota uma **arquitetura orientada a dominios modulares**, garantindo desacoplamento entre as etapas do pipeline e permitindo execucoes isoladas ou em lote.

### Estrutura do Repositorio

```text
problems-of-the-obi/
├── .gemini/                           # Governanca, engenharia de prompts e ciclo SDD
│   ├── GEMINI.md                      # Instrucoes mestras do projeto
│   ├── plans/                         # Planos tecnicos de implementacao
│   ├── prompts/                       # Historico rastreavel e metricas de tokens
│   ├── rules/                         # Regras de arquitetura e desenvolvimento Python
│   ├── skills/                        # Habilidades do Antigravity (sdd, plans, tdd)
│   └── specs/                         # Especificacoes formais de cada funcionalidade
├── cadernos/                          # Cadernos de provas originais em PDF
│   └── [ano]/[nivel]/[arquivo].pdf
├── gabaritos/                         # Arquivos ZIP brutos com testes e gabaritos
│   └── [ano]/[nivel]/[arquivo].zip
├── codigo/                            # Solucoes e codigos-fonte de referencia
│   └── [ano]/[nivel]/
├── output_question_obi/               # Base de dados estruturada do benchmark
│   └── [ano]/[nivel]/[nome-questao]/
│       ├── problem.json               # Schema padronizado de metadados e enunciado
│       └── test_cases/                # Casos de teste normalizados
│           └── inputs/
│               ├── [numero].in
|           └── outputs/
│               └── [numero].out
├── src/                               # Codigo-fonte modular da aplicacao
│   ├── core/                          # Configuracoes globais, constantes e cliente HTTP resiliente
│   │   ├── config.py
│   │   └── http_client.py
│   ├── crawler/                       # Dominio 1: Web Scraping do Portal da OBI
│   │   ├── scraper.py                 # Descoberta de links e inferencia de nivel/fase
│   │   └── cadernos_downloader.py     # Downloader de cadernos com idempotencia
│   ├── extractor/                     # Dominio 2: Extracao estruturada via LLM (Gemini/GPT)
│   ├── processor/                     # Dominio 3: Associacao, descompactacao e normalizacao de testes
│   └── reporter/                      # Dominio 4: Auditoria do dataset e documentacao
├── tests/                             # Suite de testes automatizados (TDD)
│   ├── conftest.py
│   └── unit/                          # Testes unitarios isolados por modulo
├── main.py                            # Ponto de entrada unificado e interface CLI
├── pyproject.toml                     # Gerenciamento de dependencias via uv
└── README.md                          # Documentacao do projeto
```

---

## Dominios e Pipeline de Automacao

1. **Dominio Crawler (Download de Cadernos e Gabaritos):**
   - Varre as paginas de provas da OBI (1999–2026) cobrindo todas as fases e niveis (PJ, P1, P2, Senior).
   - Realiza download resiliente e idempotente com controle de taxa de requisicoes (0.5s) e timeout estrito (15s).

2. **Dominio Extractor (Extracao via LLM):**
   - Processa os cadernos PDF atraves de APIs multimodais (Google Gemini / OpenAI).
   - Extrai enunciados, limites de tempo/memoria, secoes de entrada/saida, pontuacoes de subtarefas e categorias em schema JSON estrito (`problem.json`).

3. **Dominio Processor (Associacao e Normalizacao de Testes):**
   - Executa a correspondencia normalizada Unicode entre o nome da questao e o arquivo ZIP de gabarito.
   - Descompacta e padroniza pares identicos de casos de teste: `inputs/[numero].in` e `inputs/[numero].out`.
   - Remove residuos temporarios e descarta questoes sem casos de teste validos.

4. **Dominio Reporter (Auditoria e Relatorios):**
   - Varre o diretorio gerado, valida consistencia estrutural e atualiza dinamicamente as tabelas de progresso e estatisticas.

---

## Como Executar

### 1. Pre-requisitos
O projeto utiliza o gerenciador de ambientes Python **[uv](https://github.com/astral-sh/uv)**:

```bash
# Clonar o repositorio
git clone https://github.com/GEMA-LAB/problems-of-the-obi.git
cd problems-of-the-obi

# Criar e ativar o ambiente virtual
uv venv .venv
source .venv/bin/activate  # Linux/macOS
# ou no Windows:
.venv\Scripts\activate

# Sincronizar dependencias
uv sync
```

### 2. Execucao da Suite de Testes (TDD)
Todos os modulos sao cobertos por testes unitarios com mocks de rede:

```bash
uv run pytest -v
```

### 3. Execucao Modular via CLI (`main.py`)
A execucao pode ser realizada etapa por etapa ou em lote, com suporte a filtros por ano e nivel:

```bash
# Ajuda e listagem de parametros
uv run python main.py --help

# Download exclusivo dos cadernos de provas em PDF (Etapa 1)
uv run python main.py --step download-cadernos

# Filtrar por ano especifico (ex: 2024) e nivel especifico (ex: pj)
uv run python main.py --step download-cadernos --ano 2024 --nivel pj

# Forcar novo download de arquivos pre-existentes
uv run python main.py --step download-cadernos --force

# Executar pipeline completa (todas as etapas sequenciais)
uv run python main.py --step all
```

---

## Metodologia de Desenvolvimento (SDD e TDD)

O repositorio adota **Spec-Driven Development (SDD)** acoplado a **Test-Driven Development (TDD)**:

- **Especificacoes (`.gemini/specs/`):** Cada funcionalidade e formalmente especificada definindo objetivos, entidades, regras de negocio, invariantes e cenarios antes do codigo.
- **Planos Tecnicos (`.gemini/plans/`):** Toda funcionalidade possui plano de execucao com branch dedicada (`feat/[funcionalidade]`), commits atomicos por tarefa e criterios de aceite.
- **TDD Rigoroso:** Testes unitarios sao escritos e validados previamente a implementacao do codigo de producao em `src/`.

---

## Estatisticas do Dataset Extraido (Resultados Preliminares)

- **Total de questoes processadas:** 493
- **Com casos de teste oficiais:** 468
- **Com ilustracoes/figuras:** 188
- **Sem figuras:** 305
- **Modelo base de prova-de-conceito:** Gemini 3.1 Flash / Gemini 3.8 Flash

---

## Licenca e Uso Academico

Os enunciados e provas originais sao de titularidade do Instituto de Computacao da **Universidade Estadual de Campinas (UNICAMP)** e da organizacao da OBI. Este repositorio destina-se estritamente para **fins de pesquisa cientifica, benchmarks academicos e avaliacao educacional**.