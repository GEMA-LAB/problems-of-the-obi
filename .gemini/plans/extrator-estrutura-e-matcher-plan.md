# PLANO DE IMPLEMENTACAO: Alinhamento de Diretórios do Extrator e Correspondência Heurística de Soluções - v0.1

- **Identificador:** `extrator-estrutura-e-matcher-plan`
- **Especificação de Referência:** [`.gemini/specs/spec-extrator-estrutura-e-matcher.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-extrator-estrutura-e-matcher.md)
- **Branch de Trabalho:** `feat/extrator-estrutura-e-matcher` (criada a partir de `main`)
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md), [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md)

---

## 1. Visão Geral e Alinhamento com a Spec

Este plano visa solucionar duas inconsistências centrais identificadas no pipeline de processamento da OBI:
1. **Hierarquia e Espelhamento de Cadernos (R1, R2, R3, I1):** O extrator LLM atualmente salva questões baseando-se no campo `level` retornado pelo modelo OpenAI (que frequentemente classifica provas de "Nível 1" como `N1`, gerando a pasta espúria `output_with_code/2025/n1/`), em vez de respeitar a árvore de diretórios de origem em `cadernos/` (onde o arquivo reside em `cadernos/2025/p1/ProvaOBI2025_f1p1.pdf`). O salvamento deve espelhar rigorosamente o caminho do caderno de origem (`cadernos/[ano]/[nivel]/...` -> `output_with_code/[ano]/[nivel]/[nome_questao]/`) e normalizar os metadados em `problem.json`. Além disso, pastas já criadas de forma errônea (ex: `2025/n1`) devem ser migradas automaticamente para `2025/p1`.
2. **Correspondência Heurística Flexível de Códigos de Solução (R4, R5, R6, R7, I2):** O módulo `ResourceMatcher` falha ao associar códigos oficiais em `codigo/[ano]/[nivel]/` porque espera nomes quase idênticos ao título da questão. No repositório real da OBI, arquivos em `codigo/2025/p1/` possuem variações de autor, estratégia e prefixos abreviados (ex: `recarga_carro.cpp`, `recarga_lobo_bb.cpp` para `Recarga`; `redes_1_freq_java.java`, `redes_andre.cpp` para `Redes de Descanso`; `cabo_carol.py` para `Cabo de Guerra`; `feira_artesanato_cpp.cpp` para `Feira de Artesanato`). O matcher deve implementar correspondência resiliente com base em prefixos antes de separadores (`_`, `-`), slug reverso, e interseção de tokens semânticos (desconsiderando stopwords e termos técnicos auxiliares).

---

## 2. Modulos Impactados e Contratos de Interface

```text
problems-of-the-obi/
├── .gemini/
│   ├── plans/
│   │   └── extrator-estrutura-e-matcher-plan.md     # Este plano de implementação
│   └── specs/
│       └── spec-extrator-estrutura-e-matcher.md     # Especificação de referência
├── src/
│   ├── extractor/
│   │   └── openai_extractor.py                      # Propagação do source_pdf e cálculo de pasta a partir de cadernos/
│   └── processor/
│       ├── matcher.py                               # Implementação das 4 heurísticas de correspondência de soluções
│       ├── cleaner.py                               # Função de saneamento e migração de pastas legadas (n1 -> p1)
│       └── questions_organizer.py                   # Integração do matcher aprimorado e migração inicial
├── tests/
│   └── unit/
│       ├── test_openai_extractor.py                 # Testes de persistência com espelhamento da árvore de cadernos
│       ├── test_matcher.py                          # Testes com casos reais (recarga_carro, redes_1_freq, feira_artesanato, fila)
│       └── test_cleaner.py                          # Testes de migração de pastas legadas
└── output_with_code/                                # Saneamento da pasta 2025/n1 -> 2025/p1
```

### Contratos de Interface

#### 1. `OpenAiExtractor.save_problem` (`src/extractor/openai_extractor.py`)
```python
def save_problem(
    self,
    problem: ProblemSchema,
    output_base: Optional[Path] = None,
    source_pdf: Optional[Path] = None,
    base_cadernos_dir: Optional[Path] = None,
) -> Path:
    """
    Salva o problema garantindo que a estrutura output_with_code/[ano]/[nivel]/
    espelhe a pasta de origem cadernos/[ano]/[nivel]/ do source_pdf.
    Se source_pdf for fornecido, ano e nivel sao derivados estritamente dele.
    """
```

#### 2. `ResourceMatcher.find_solutions` (`src/processor/matcher.py`)
```python
def find_solutions(
    self,
    question: QuestionFolder,
    matcher_alias: Optional[str] = None,
) -> List[SolutionSource]:
    """
    Busca solucoes no diretorio codigo/[ano]/[nivel]/ aplicando 4 heurísticas:
    1. Exatidão normalizada (stem == slug)
    2. Prefixo por separador ('recarga_carro' -> 'recarga' == slug ou target_slug.startswith(prefix))
    3. Slug reverso (stem_norm.startswith(target_slug))
    4. Interseção de tokens significativos sem stopwords
    """
```

#### 3. `DatasetCleaner.migrate_legacy_directories` (`src/processor/cleaner.py`)
```python
def migrate_legacy_directories(
    self,
    output_dir: Path,
    cadernos_dir: Path,
) -> int:
    """
    Identifica pastas em output_dir que nao existem em cadernos_dir (ex: 2025/n1)
    e move as questoes para o nivel correto (ex: 2025/p1), removendo diretorios orfaos.
    """
```

---

## 3. Checklist de Execucao por Tasks (Commits Atomicos)

Conforme a diretriz do fluxo da skill `plans`, a execução deve ocorrer na branch `feat/extrator-estrutura-e-matcher` com commits atômicos por tarefa:

### [x] Task 1: Criacao da Branch e Testes Unitarios (TDD)
- Criar e mudar para a branch `feat/extrator-estrutura-e-matcher` a partir de `main`.
- Adicionar casos de teste em `tests/unit/test_matcher.py` simulando os arquivos reais de `codigo/2025/p1/`:
  - `recarga_carro.cpp`, `recarga_pedro_union_find.cpp` -> `Recarga`
  - `redes_1_freq_java.java`, `redes_andre.cpp` -> `Redes de Descanso`
  - `feira_artesanato_py.py`, `feira.java` -> `Feira de Artesanato`
  - `fila_c.c`, `fila_cpp.cpp` -> `Fila`
  - Desambiguação de homônimos / subconjuntos (`fila.java` vs `fila_cantina.cpp`).
- Adicionar casos de teste em `tests/unit/test_openai_extractor.py` garantindo que `save_problem` com `source_pdf = cadernos/2025/p1/ProvaOBI2025_f1p1.pdf` salve em `output_with_code/2025/p1/` e normalize `level` para `p1`, mesmo se o JSON da LLM contiver `"level": "N1"`.
- **Commit:** `0e0f0e2c test(matcher): add test cases for flexible solution matching and cadernos directory mirroring`

### [x] Task 2: Implementacao do Espelhamento de Cadernos no Extrator
- Modificar `OpenAiExtractor.save_problem` e `OpenAiExtractor.process_cadernos` em `src/extractor/openai_extractor.py`:
  - Derivar `ano` e `nivel` do caminho relativo do PDF em relação a `cadernos/`.
  - Normalizar `problem.year` e `problem.level` para os valores do diretório (`p1`, `p2`, `pj`, `senior`, `geral`).
  - Manter compatibilidade com chamadas existentes sem `source_pdf`.
- Executar os testes de `test_openai_extractor.py` para validar conformidade.
- **Commit:** `96c65dd3 feat(extractor): mirror cadernos directory structure and normalize problem level`

### [x] Task 3: Implementacao da Correspondencia Heuristica de Solucoes
- Atualizar `src/processor/matcher.py`:
  - Implementar lista de stopwords da língua portuguesa (`de`, `da`, `do`, `dos`, `das`, `e`, `com`, `para`, `em`, `a`, `o`, `um`, `uma`).
  - Implementar lista de tokens técnicos ignoráveis (`solucao`, `reference`, `aluno`, `cpp`, `py`, `java`, `js`, `andre`, `bez`, `sorting`, `matriz`).
  - Implementar as 4 camadas heurísticas em `find_solutions`.
  - Priorizar escopo `codigo/[ano]/[nivel]/`.
  - Implementar desambiguação por especificidade de tokens/comprimento de prefixo.
- Executar os testes de `test_matcher.py` e validar 100% de sucesso.
- **Commit:** `04a39255 feat(matcher): implement resilient heuristic solution code matching`

### [x] Task 4: Modulo de Migracao e Saneamento de Diretorios Legados
- Implementar `migrate_legacy_directories` em `src/processor/cleaner.py`:
  - Mapear equivalências conhecidas (ex: `n1` em 2025 para `p1` com base nos cadernos de prova).
  - Mover diretórios de questões existentes com segurança (`shutil.move` / `rename`).
  - Remover pastas obsoletas órfãs.
- Integrar a chamada de saneamento em `QuestionsOrganizer.discover_questions` ou método de setup.
- Criar testes unitários em `tests/unit/test_cleaner.py`.
- **Commit:** `8f7e65da feat(processor): add legacy directory migration for output_with_code`

### [x] Task 5: Saneamento Local do Dataset e Organizacao de Solucoes
- Executar a rotina de saneamento no dataset local:
  - Migrar `output_with_code/2025/n1/` (`Café com Leite`, `Fila`, `Pizzaria`) para `output_with_code/2025/p1/`.
  - Excluir o diretório residual `output_with_code/2025/n1/`.
- Executar o CLI `python main.py --step organize-questions --ano 2025 --nivel p1` para verificar se os códigos de `codigo/2025/p1/` agora são corretamente copiados para as pastas `solutions/` de `Fila`, `Recarga`, `Redes de Descanso`, `Diagonal`, etc.
- **Commit:** `f7ae82ca fix(dataset): migrate 2025 n1 questions to p1 and organize solutions`

### [x] Task 6: Execucao da Suite Completa de Testes e Abertura de Pull Request
- Executar `uv run pytest` em toda a suíte de testes (111 testes passando com 100% de sucesso).
- Confirmar as invariantes I1, I2 e I3 da especificação.
- Conforme o fluxo da skill `plans`, fazer push da branch `feat/extrator-estrutura-e-matcher` e abrir Pull Request listando todas as alterações.
- **Commit / PR:** `docs(plans): finalize extrator-estrutura-e-matcher plan and submit pull request`

---

## 4. Estrategia de Testes (TDD)

1. **`test_openai_extractor.py`**:
   - `test_save_problem_mirrors_cadernos_path`: PDF em `cadernos/2025/p1/Prova.pdf` com LLM retornando `"level": "N1"` DEVE salvar em `output_with_code/2025/p1/[titulo]/problem.json`.
   - `test_save_problem_normalizes_problem_level`: O JSON salvo em disco deve conter `"level": "p1"`.
   - `test_save_problem_fallback_without_source_pdf`: Mantém compatibilidade com chamadas diretas legadas.

2. **`test_matcher.py`**:
   - `test_find_solutions_prefix_matching`: Casamento de `recarga_carro.cpp` e `recarga_lobo_bb.cpp` com questão `Recarga`.
   - `test_find_solutions_token_intersection`: Casamento de `redes_1_freq_java.java` com questão `Redes de Descanso`.
   - `test_find_solutions_author_and_variant`: Casamento de `feira_artesanato_cpp.cpp` e `feira.java` com `Feira de Artesanato`.
   - `test_find_solutions_disambiguation`: `fila.java` casa com `Fila`, enquanto `fila_cantina.cpp` casa com `Fila na Cantina`.

3. **`test_cleaner.py`**:
   - `test_migrate_legacy_directories`: Move subdiretórios de `output_with_code/2025/n1` para `output_with_code/2025/p1` e remove a pasta `n1`.

---

## 5. Criterios de Aceite

- [x] A branch de trabalho é `feat/extrator-estrutura-e-matcher` criada a partir de `main`.
- [x] O extrator `OpenAiExtractor` nunca cria pastas que não existam sob `cadernos/[ano]/` (ex: `n1`).
- [x] O arquivo `problem.json` reflete o nível canônico (`pj`, `p1`, `p2`, `senior`, `geral`) derivado do caderno.
- [x] A pasta `output_with_code/2025/n1` é migrada para `output_with_code/2025/p1` e removida.
- [x] O matcher de soluções associa com sucesso códigos com prefixos de autor e variações em `codigo/2025/p1/` (ex: `recarga`, `redes`, `feira`, `fila`).
- [x] Cada tarefa possui um commit atômico no padrão conventional commits.
- [x] A suíte completa de testes passa com 100% de sucesso via `uv run pytest` (111 testes).
- [x] Pull Request aberto listando todas as alterações.
- [x] Nenhum emoji utilizado em código, commits ou documentação.

