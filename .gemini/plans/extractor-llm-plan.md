# PLANO DE IMPLEMENTACAO: Extrator LLM de Questoes via API OpenAI - v0.1

- **Identificador:** `extractor-llm-plan`
- **Especificacao de Referencia:** [`.gemini/specs/spec-extractor-llm.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-extractor-llm.md)
- **Branch de Trabalho:** `feat/extractor-llm` (criada a partir de `main`)
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md), [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md)

---

## 1. Visao Geral e Alinhamento com a Spec

Implementar de forma modular, desacoplada, resiliente e rigorosamente testada (TDD) o dominio de extracao de questoes da OBI a partir de cadernos de prova em PDF utilizando a biblioteca oficial da OpenAI, cumprindo integralmente os requisitos da especificacao:
1. **Biblioteca Oficial da OpenAI (R1, PC1):** Integracao direta com `openai.OpenAI`, consumindo `OPENAI_BASE_URL`, `OPENAI_API_KEY` e `OPENAI_MODEL` a partir do `.env`.
2. **Envio via Files API e Limpeza Mandatoria (R2, R8, I1):** Upload de arquivos PDF utilizando `client.files.create(file=f, purpose="assistants")` e garantia estrita de exclusao via `client.files.delete` no bloco `finally`.
3. **Calibracao de Limites para Python e Remocao de Dificuldade (R3, I2):** Instrucao estrita no prompt para interpretar `time_limit` (float, em segundos) e `memory_limit` (int, em MB) com foco na resolucao do problema em linguagem Python, eliminando categoricamente o campo `difficulty`.
4. **Sanitizacao e Tolerancia a Falhas (R4, R5):** Sanitizacao robusta de markdown fences (```json ... ```) e validacao sintatica e de schema via Pydantic/dataclasses.
5. **Estrutura de Saida e Resolucao de Conflitos (R6, R7, I3):** Salvamento consistente em `output/[titulo]/problem.json` e sufixo `output/[titulo]_[ano]/` em caso de questoes homonimas de anos diferentes, com sanitizacao de caracteres especiais e formatacao `indent=4`, `ensure_ascii=False`.
6. **Integracao Modular no CLI (`main.py`):** Integracao transparente na etapa `--step extract-questions` com suporte a execucao individual ou contínua no pipeline.

---

## 2. Modelagem de Dados e Entidades

### `ProblemSchema` e `Exemplo` (`src/models/problem.py`)
```python
from dataclasses import dataclass, field
from typing import List, Optional

@dataclass
class Exemplo:
    input: str
    output: str

@dataclass
class ProblemSchema:
    title: str
    statement: str
    input: str
    output: str
    constraints: str
    examples: List[Exemplo]
    imgs: List[str] = field(default_factory=list)
    rating: List[int] = field(default_factory=list)
    year: str = ""
    level: str = ""
    period: str = ""
    topics: List[str] = field(default_factory=list)
    time_limit: float = 1.0
    memory_limit: int = 256
```

### `ExtractorConfig` (`src/core/config.py`)
```python
@dataclass(frozen=True)
class ExtractorConfig:
    base_url: Optional[str] = None
    api_key: Optional[str] = None
    model: str = "gpt-4o-mini"
    prompt_template_path: Path = Path("src/prompts/extraction_prompt.md")
    pasta_entrada: Path = Path("cadernos")
    pasta_output: Path = Path("output")
```

---

## 3. Modulos Afetados e Estrutura de Arquivos

```text
problems-of-the-obi/
├── .env.example                          # Configuracoes da API da OpenAI
├── .env                                  # Variaveis de ambiente locais
├── .gemini/
│   ├── plans/
│   │   └── extractor-llm-plan.md         # Este documento de planejamento
│   ├── prompts/
│   │   └── 022-criar-plano-extractor-llm.md
│   └── specs/
│       └── spec-extractor-llm.md         # Especificacao de referencia
├── src/
│   ├── core/
│   │   └── config.py                     # ExtractorConfig e constantes da OpenAI
│   ├── models/
│   │   ├── __init__.py
│   │   └── problem.py                    # Modelos ProblemSchema e Exemplo sem difficulty
│   ├── prompts/
│   │   └── extraction_prompt.md          # Template oficial do prompt com limites para Python
│   └── extractor/
│       ├── __init__.py
│       ├── prompt_loader.py              # Carregamento e renderizacao do template de prompt
│       ├── json_parser.py                # Sanitizacao de markdown e desserializacao estruturada
│       └── openai_extractor.py           # Cliente OpenAI, Files API, processamento e gravacao
├── tests/
│   └── unit/
│       ├── test_models_problem.py        # Testes unitarios do schema ProblemSchema
│       ├── test_prompt_loader.py         # Testes de carregamento do template de prompt
│       ├── test_json_parser.py           # Testes de sanitizacao de markdown e parsing JSON
│       └── test_openai_extractor.py      # Testes do extrator OpenAI (com mocks de Files e Responses)
└── main.py                               # Conexao da etapa extract-questions ao OpenAiExtractor
```

---

## 4. Checklist de Execucao por Tasks (Commits Atomicos)

Conforme a diretriz da skill `plans`, a execucao ocorreu na branch `feat/extractor-llm` com commits atomicos individuais por tarefa:

### [x] Task 1: Configuracao da Branch e Modelos de Dominio (`ProblemSchema`)
- Criar a branch `feat/extractor-llm` a partir de `main`.
- Adicionar `ExtractorConfig` e constantes de OpenAI em `src/core/config.py`.
- Implementar `ProblemSchema` e `Exemplo` em `src/models/problem.py` com validacao de tipos, limites `time_limit` e `memory_limit` e sem o campo `difficulty`.
- Criar testes unitarios em `tests/unit/test_models_problem.py`.
- **Commit:** `7820e953 feat(models): create ProblemSchema with python limits and ExtractorConfig`

### [x] Task 2: Template de Prompt e Prompt Loader
- Criar o template de prompt versionado em `src/prompts/extraction_prompt.md`:
  - Persona e task especializadas na OBI.
  - Regras estritas: sem `difficulty`, com `time_limit` e `memory_limit` calibrados para viabilizar resolucao em linguagem Python.
  - Formato JSON em array de objetos.
- Implementar `PromptLoader` em `src/extractor/prompt_loader.py`.
- Criar testes unitarios em `tests/unit/test_prompt_loader.py`.
- **Commit:** `abc13847 feat(extractor): add extraction prompt template and prompt loader`

### [x] Task 3: Sanitizacao e Parsing de JSON Tolerante a Falhas
- Implementar `sanitize_json_markdown` e `parse_problems_json` em `src/extractor/json_parser.py`:
  - Limpeza de fences ````json ... ```` ou ```` ... ````.
  - Extracao tolerante de arrays JSON validos com `json.loads`.
  - Conversao de dicionarios brutos para instancias de `ProblemSchema`.
  - Tratamento de excecoes de JSONDecodeError retornando lista vazia e registrando detalhes do erro.
- Criar testes unitarios exaustivos em `tests/unit/test_json_parser.py` (JSON valido, JSON com markdown, JSON com texto periferico, JSON invalido).
- **Commit:** `c6f906b5 feat(extractor): implement markdown sanitization and json parser`

### [x] Task 4: Modulo `OpenAiExtractor` com Files API e Exclusao Mandatoria
- Implementar `OpenAiExtractor` em `src/extractor/openai_extractor.py`:
  - Inicializacao com `ExtractorConfig` ou cliente `OpenAI` injetado.
  - Metodo `extract_from_pdf(pdf_path: Path) -> list[ProblemSchema]`:
    - Envio do arquivo via `client.files.create(file=f, purpose="assistants")`.
    - Requisicao com modelo OpenAI configurado.
    - Bloco `finally` garantindo `client.files.delete(file_id)` mesmo em caso de erro.
  - Metodo `save_problem(problem: ProblemSchema, output_base: Path)`:
    - Gravacao em `output/[titulo]/problem.json` com `indent=4` e `ensure_ascii=False`.
    - Resolucao de conflitos por ano em `output/[titulo]_[ano]/` e sanitizacao de caracteres especiais.
  - Metodo `process_cadernos(cadernos: list[Path]) -> tuple[list[ProblemSchema], list[Path]]`:
    - Processamento de multiplos PDFs com retencao de falhas para repeticao ciclica.
- Criar suite de testes com mocks em `tests/unit/test_openai_extractor.py`.
- **Commit:** `174c8de9 feat(extractor): implement OpenAiExtractor with Files API and lifecycle cleanup`

### [x] Task 5: Integracao no CLI (`main.py`) e Validacao End-to-End
- Integrar `OpenAiExtractor` no fluxo de `--step extract-questions` e pipeline geral em `main.py`.
- Suporte a filtros de `--ano` e `--nivel` para selecao de cadernos PDF.
- Atualizar documentacao do CLI e garantir que `uv run pytest` passe com 100% de sucesso.
- **Commit:** `c5e68ea5 feat(cli): integrate OpenAiExtractor into main pipeline CLI`

### [x] Task 6: Finalizacao e Abertura de Pull Request
- Executar suite completa de testes unitarios e de integracao (74 testes passando).
- Confirmar conformidade estrita com as invariantes I1, I2 e I3.
- Submeter branch e abrir Pull Request detalhando as mudancas conforme a skill `plans`.
- **Commit / PR:** `docs: finalize extractor-llm implementation plan and submit pull request`

---

## 5. Estrategia de Testes (TDD)

1. **`test_models_problem.py`:**
   - Validar instanciacao de `ProblemSchema` com valores padrao e informados.
   - Validar serializacao para dicionario/JSON preservando tipos `float` para `time_limit` e `int` para `memory_limit`.
   - Garantir que o campo `difficulty` nao faca parte dos atributos do modelo.

2. **`test_prompt_loader.py`:**
   - Validar leitura do template markdown e confirmacao da presenca das instrucoes para limites em Python.

3. **`test_json_parser.py`:**
   - Validar extracao correta a partir de resposta limpa.
   - Validar extracao a partir de blocos cercados por ```json ... ```.
   - Validar retorno seguro em caso de JSON truncado ou invalido.

4. **`test_openai_extractor.py`:**
   - Simular resposta da API com mock e verificar chamada obrigatoria a `client.files.delete` no `finally`.
   - Verificar resolucao de colisoes de nomes de questoes com anos diferentes.
   - Testar gravacao com `indent=4` e `ensure_ascii=False`.

---

## 6. Criterios de Aceite

- [x] Todos os novos modulos estao localizados em `src/extractor/`, `src/models/` e `src/prompts/`.
- [x] O modelo `ProblemSchema` nao contem `difficulty` e contem `time_limit` (float) e `memory_limit` (int) voltados para Python.
- [x] Todo arquivo enviado a API da OpenAI e deletado no `finally` sem retencao residual.
- [x] Os arquivos sao salvos estritamente em `output/[titulo]/problem.json` (ou `output/[titulo]_[ano]/`).
- [x] A suite completa de testes passa com 100% de sucesso via `uv run pytest`.
- [x] Nenhum emoji utilizado em arquivos de codigo, commits ou documentacao.
