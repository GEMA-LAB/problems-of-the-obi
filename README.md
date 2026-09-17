# Banco de Problemas OBI — Repositório para Experimentos e Avaliação

Este repositório centraliza, padroniza e disponibiliza problemas da **Olimpíada Brasileira de Informática (OBI)** em formato estruturado (`JSON`), associando casos de teste padronizados para suportar experimentos em avaliação de Modelos de Linguagem (LLMs), sistemas de correção automática e pesquisa em inteligência artificial aplicada à programação competitiva.

- **Fonte de dados oficial:** [Provas Passadas OBI - Unicamp](https://olimpiada.ic.unicamp.br/passadas/)
- **Objetivo Científico:** Criação de um benchmark reprodutível, testável e anotado para avaliar o raciocínio lógico e algorítmico de LLMs em português.

---

## 🏛️ Arquitetura e Engenharia de Software

O projeto adota uma **arquitetura orientada a domínios modulares**, garantindo desacoplamento entre as etapas do pipeline e permitindo execuções isoladas ou em lote.

### Estrutura do Repositório

```text
problems-of-the-obi/
├── .gemini/                           # Governança, engenharia de prompts e ciclo SDD
│   ├── GEMINI.md                      # Instruções mestras do projeto
│   ├── plans/                         # Planos técnicos de implementação
│   ├── prompts/                       # Histórico rastreável e métricas de tokens
│   ├── rules/                         # Regras de arquitetura e desenvolvimento Python
│   ├── skills/                        # Habilidades do Antigravity (sdd, plans, tdd)
│   └── specs/                         # Especificações formais de cada funcionalidade
├── cadernos/                          # Cadernos de provas originais em PDF
│   └── [ano]/[nivel]/[arquivo].pdf
├── gabaritos/                         # Arquivos ZIP brutos com testes e gabaritos
│   └── [ano]/[nivel]/[arquivo].zip
├── codigo/                            # Soluções e códigos-fonte de referência
│   └── [ano]/[nivel]/
├── output_question_obi/               # Base de dados estruturada do benchmark
│   └── [ano]/[nivel]/[nome-questao]/
│       ├── problem.json               # Schema padronizado de metadados e enunciado
│       └── test_cases/                # Casos de teste normalizados
│           └── inputs/
│               ├── [numero].in
│               └── [numero].out
├── src/                               # Código-fonte modular da aplicação
│   ├── core/                          # Configurações globais, constantes e HTTP client resiliente
│   │   ├── config.py
│   │   └── http_client.py
│   ├── crawler/                       # Domínio 1: Web Scraping do Portal da OBI
│   │   ├── scraper.py                 # Descoberta de links e inferência de nível/fase
│   │   └── cadernos_downloader.py     # Downloader de cadernos com idempotência
│   ├── extractor/                     # Domínio 2: Extração estruturada via LLM (Gemini/GPT)
│   ├── processor/                     # Domínio 3: Associação, descompactação e normalização de testes
│   └── reporter/                      # Domínio 4: Auditoria do dataset e documentação
├── tests/                             # Suíte de testes automatizados (TDD)
│   ├── conftest.py
│   └── unit/                          # Testes unitários isolados por módulo
├── main.py                            # Ponto de entrada unificado e interface CLI
├── pyproject.toml                     # Gerenciamento de dependências via uv
└── README.md                          # Este documento
```

---

## ⚙️ Domínios e Pipeline de Automação

1. **📄 Domínio Crawler (Download de Cadernos e Gabaritos):**
   - Varre as páginas de provas da OBI (1999–2026) cobrindo todas as fases e níveis (PJ, P1, P2, Sênior).
   - Realiza download resiliente e idempotente com controle de *rate limit* (0.5s) e timeout estrito (15s).

2. **🤖 Domínio Extractor (Extração via LLM):**
   - Processa os cadernos PDF através de APIs multimodais (Google Gemini / OpenAI).
   - Extrai enunciados, limites de tempo/memória, seções de entrada/saída, pontuações de subtarefas e categorias em schema JSON estrito (`problem.json`).

3. **📦 Domínio Processor (Associação e Normalização de Testes):**
   - Faz o cruzamento fonético/Unicode entre o nome da questão e o arquivo ZIP de gabarito.
   - Descompacta e normaliza pares idênticos de casos de teste: `inputs/[numero].in` e `inputs/[numero].out`.
   - Remove resíduos temporários e descarta questões sem casos de teste válidos.

4. **📝 Domínio Reporter (Auditoria e Relatórios):**
   - Varre o diretório gerado, valida consistência e atualiza dinamicamente as tabelas de progresso e estatísticas.

---

## 🚀 Como Executar

### 1. Pré-requisitos
O projeto utiliza o gerenciador rápido de ambientes Python **[uv](https://github.com/astral-sh/uv)**:

```bash
# Clone o repositório
git clone https://github.com/GEMA-LAB/problems-of-the-obi.git
cd problems-of-the-obi

# Crie e ative o ambiente virtual
uv venv .venv
source .venv/bin/activate  # No Linux/macOS
# ou no Windows:
.venv\Scripts\activate

# Sincronize as dependências
uv sync
```

### 2. Execução da Suíte de Testes (TDD)
Todos os módulos são cobertos por testes unitários e de integração utilizando mocks:

```bash
uv run pytest -v
```

### 3. Execução Modular via CLI (`main.py`)
A execução pode ser feita etapa por etapa ou em lote, com suporte a filtros por ano e nível:

```bash
# Ajuda e listagem de parâmetros
uv run python main.py --help

# Download apenas dos cadernos de provas em PDF (Etapa 1)
uv run python main.py --step download-cadernos

# Filtrar por ano específico (ex: 2024) e nível específico (ex: pj)
uv run python main.py --step download-cadernos --ano 2024 --nivel pj

# Forçar re-download de arquivos existentes
uv run python main.py --step download-cadernos --force

# Executar pipeline completa (todas as etapas sequenciais)
uv run python main.py --step all
```

---

## 🧪 Metodologia de Desenvolvimento (SDD & TDD)

O repositório adota **Spec-Driven Development (SDD)** acoplado a **Test-Driven Development (TDD)** e governança pelo Antigravity:

- **Especificações (`.gemini/specs/`):** Cada funcionalidade é especificada formalmente definindo objetivos, entidades, regras de negócio, invariantes e cenários BDD antes da escrita de código.
- **Planos Técnicos (`.gemini/plans/`):** Toda feature possui um plano de execução com branch dedicada (ex: `feat/[funcionalidade]`), commits atômicos por tarefa e critérios de aceite.
- **TDD Rigoroso:** O teste unitário com mocks de rede é escrito e validado antes da implementação do código de produção em `src/`.

---

## 📊 Estatísticas do Dataset Extraído (Resultados Preliminares)

- **Total de questões processadas:** 493
- **Com casos de teste oficiais:** 468
- **Com ilustrações/figuras:** 188
- **Sem figuras:** 305
- **Modelo base de prova-de-conceito:** Gemini 3.1 Flash / Gemini 3.8 Flash

---

## 📄 Licença e Uso Acadêmico

Os enunciados e provas originais são de titularidade do Instituto de Computação da **Universidade Estadual de Campinas (UNICAMP)** e da organização da OBI. Este repositório destina-se estritamente para **fins de pesquisa científica, benchmarks acadêmicos e avaliação educacional**.