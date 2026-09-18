# PLANO DE IMPLEMENTAÇÃO: Organização de Questões, Gabaritos e Soluções (Organize Questions) - v0.1

- **Identificador:** `organize-questions-plan`
- **Especificação de Referência:** [`.gemini/specs/spec-organize-questions.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-organize-questions.md)
- **Branch de Trabalho:** `feat/organize-questions` (criada a partir de `main`)
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md), [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md)
- **Regras Arquiteturais:** [`.gemini/rules/architecture-programming-mode.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/rules/architecture-programming-mode.md), [`.gemini/rules/python-developer.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/rules/python-developer.md)

---

## 1. Visão Geral e Alinhamento com a Especificação

Implementar de forma modular, desacoplada, resiliente e rigorosamente orientada por testes (TDD) o domínio de processamento e organização de questões (`src/processor/`). Este módulo é responsável por:
1. **Correspondência Robusta com Normalização Unicode Estrita (R1):** Cruzar as pastas de questões estruturadas em `output_with_code/` (ou `output_question_obi/` / `output/`) com os arquivos de gabarito (.zip em `gabaritos/`) e códigos de solução oficial (`codigo/`) utilizando decomposição canônica NFD, remoção de diacríticos/acentos, pontuações, hífens, espaços e conversão para minúsculas.
2. **Descompactação Segura de Gabaritos (R2, R8, I1):** Descompactar os arquivos ZIP de gabarito para uma área de processamento temporária antes de mover/estruturar os arquivos em `test_cases/`, tratando ZIPs corrompidos ou ilegíveis sem interromper a execução do pipeline.
3. **Idempotência Estrita (R3, E2):** Se a subpasta `test_cases/` já contiver casos de teste válidos e estruturados e o parâmetro `force=False` for fornecido, pular o processamento para preservar I/O e estado consolidado.
4. **Normalização Sequencial de Pares de Teste (R4, I2):** Parear com rigor biunívoco 1-para-1 cada arquivo de entrada com seu respectivo arquivo de saída (`.in` com `.out` ou `.sol`), ordená-los de forma natural e renomeá-los sequencialmente a partir de 1 (`1.in`, `1.out`, `2.in`, `2.out`, etc.), alocando-os nas subpastas padronizadas `test_cases/inputs/[numero].in` e `test_cases/outputs/[numero].out` (mantendo também links/arquivos em `test_cases/`).
5. **Expurgo de Resíduos e Lixo Compilado (R5):** Excluir categoricamente de `test_cases/` quaisquer arquivos binários compilados (`.exe`, `.o`), arquivos temporários ou sobras que não sejam os arquivos de teste normalizados.
6. **Organização de Soluções Oficiais (R6, I3):** Copiar ou extrair todos os códigos-fonte e arquivos pertinentes de soluções oficiais presentes em `codigo/` para a subpasta isolada `solutions/` da questão, garantindo separação física estrita entre casos de teste e códigos.
7. **Consistência do Dataset e Remoção de Questões Inválidas (R7, E3, I4):** Remover a pasta da questão caso ela não possua nenhum par válido de teste após o processamento, assegurando que o dataset final contenha apenas problemas completos e testáveis. Preservar estritamente `problem.json` e `imgs/` das questões válidas (Invariante I1).
8. **Integração no CLI com Retrocompatibilidade (R9):** Integrar o novo orquestrador `QuestionsOrganizer` no CLI [`main.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/main.py) sob a etapa `--step organize-questions`, mantendo o alias `--step organize-testcases` para compatibilidade, além de suportar os filtros `--ano`, `--nivel` e a flag `--force`.

---

## User Review Required

> [!IMPORTANT]
> **Compatibilidade de Diretórios de Saída:**
> O projeto recentemente padronizou o diretório de questões com soluções em `output_with_code/[ano]/[nivel]/[nome_questao]/` (conforme prompt 024 e `DEFAULT_OUTPUT_DIR` em `src/core/config.py`), enquanto a especificação e arquitetura referenciam também `output_question_obi/` e `output/`. O `OrganizeConfig` e o leitor de questões serão implementados para aceitar dinamicamente qualquer um dos caminhos, com detecção automática e prioridade para `output_with_code/` (ou caminho explicitamente configurado pelo usuário).

> [!NOTE]
> **Diretório dos Pares de Teste:**
> A especificação `spec-organize-questions.md` e a regra de arquitetura definem `test_cases/inputs/[numero].in` e `test_cases/outputs/[numero].out`. O normalizador gerará essa estrutura padronizada em subpastas dedicadas `inputs/` e `outputs/`, garantindo compatibilidade também com scripts que buscam diretamente em `test_cases/`.

---

## Open Questions

Não há dúvidas bloqueantes ou ambiguidades no escopo da especificação. Todos os requisitos, invariantes e cenários de exceção estão claramente mapeados.

---

## Proposed Changes

```
problems-of-the-obi/
├── .gemini/
│   ├── plans/
│   │   └── organize-questions-plan.md     # Plano registrado na base de conhecimento
│   └── prompts/
│       └── 025-criar-plano-organize-questions.md
├── src/
│   ├── core/
│   │   └── config.py                     # Constantes de diretórios de teste e OrganizeConfig
│   ├── models/
│   │   ├── __init__.py
│   │   └── test_case.py                  # Entidades QuestionFolder, TestCasePair, OrganizeResult, etc.
│   └── processor/                        # Domínio 3 (Clean Architecture)
│       ├── __init__.py
│       ├── matcher.py                    # Normalização Unicode NFD e correspondência questão <-> gabarito/código
│       ├── zip_extractor.py              # Extração segura e tolerante a falhas de arquivos compactados
│       ├── normalizer.py                 # Descoberta, pareamento 1-1 e renumeração sequencial de casos de teste
│       ├── cleaner.py                    # Limpeza de lixo (.exe, .o) e expurgo de questões sem testes
│       └── questions_organizer.py        # Orquestrador do fluxo completo de organização
├── tests/
│   └── unit/
│       ├── test_models_test_case.py      # Testes unitários das entidades de domínio
│       ├── test_matcher.py               # Testes de normalização e busca de matches fonéticos/textuais
│       ├── test_zip_extractor.py         # Testes de descompactação e resiliência a ZIP corrompido
│       ├── test_normalizer.py            # Testes de pareamento e renumeração sequencial
│       ├── test_cleaner.py               # Testes de limpeza de resíduos e remoção de pastas inválidas
│       ├── test_questions_organizer.py   # Testes unitários e de fluxo do QuestionsOrganizer
│       └── test_cli.py                   # Testes da invocação do CLI para organize-questions
└── main.py                               # Substituição dos métodos legados pelo QuestionsOrganizer
```

---

### Componente 1: Modelos de Domínio e Configurações

Definição dos modelos de dados tipados estritamente alinhados com a seção **Entidades** da especificação.

#### [NEW] [`src/models/test_case.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/models/test_case.py)
- Modelos dataclass imutáveis/validados:
  - `QuestionFolder`: `path: Path`, `ano: int`, `nivel: str`, `titulo: str`, `titulo_normalizado: str`.
  - `TestCasePair`: `id: int`, `input_file: Path` (`.in`), `output_file: Path` (`.out`).
  - `TestCaseSource`: `path_zip: Path`, `ano: int`, `nivel: str`, `nome_normalizado: str`.
  - `SolutionSource`: `path_arquivo: Path`, `ano: int`, `nivel: str`, `nome_normalizado: str`, `linguagem: str`.
  - `OrganizeConfig`: `pasta_output: Path`, `pasta_gabaritos: Path`, `pasta_codigo: Path`, `force: bool`.
  - `OrganizeResult`: `questao: str`, `test_pairs: list[TestCasePair]`, `solutions_count: int`, `status: str` (`sucesso`, `parcial`, `sem_recursos`, `removido_sem_testes`).

#### [MODIFY] [`src/models/__init__.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/models/__init__.py)
- Exportar as novas entidades `QuestionFolder`, `TestCasePair`, `TestCaseSource`, `SolutionSource`, `OrganizeConfig`, `OrganizeResult`.

#### [MODIFY] [`src/core/config.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/core/config.py)
- Adicionar constantes:
  - `DEFAULT_TEST_CASES_DIR = Path("test_cases")`
  - `DEFAULT_SOLUTIONS_DIR = Path("solutions")`
  - `DEFAULT_INPUTS_DIR = Path("inputs")`
  - `DEFAULT_OUTPUTS_DIR = Path("outputs")`
  - `EXTENSOES_ENTRADA_TESTE = (".in", ".input")`
  - `EXTENSOES_SAIDA_TESTE = (".out", ".output", ".sol")`
- Adicionar/reexportar `OrganizeConfig` com valores padrão integrados ao pipeline.

---

### Componente 2: Módulo de Correspondência (`matcher.py`)

Implementação de normalização Unicode estrita e heurísticas de correspondência de nomes.

#### [NEW] [`src/processor/matcher.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/processor/matcher.py)
- Função `normalize_name(name: str) -> str`:
  - Aplica `unicodedata.normalize('NFD', name)`.
  - Remove acentos e caracteres não-espaço (`Mn`).
  - Converte para minúsculas (`lower()`).
  - Remove pontuações, traços, sublinhados e caracteres não alfanuméricos.
  - Remove espaços em branco residuais.
- Classe `ResourceMatcher`:
  - Indexa arquivos de gabarito em `gabaritos/[ano]/[nivel]/[nome].zip` gerando catálogo indexado por `(ano, nivel, slug)`.
  - Indexa arquivos e zips de solução em `codigo/[ano]/[nivel]/` gerando catálogo indexado por `(ano, nivel, slug)`.
  - Método `find_gabarito(question: QuestionFolder) -> Optional[TestCaseSource]`:
    - Busca match exato por `(ano, nivel, slug)`.
    - Fallback para busca por `(ano, slug)` se o nível for genérico.
    - Fallback tolerante para substrings (ex: prefixo ou sufixo correspondente).
  - Método `find_solutions(question: QuestionFolder) -> list[SolutionSource]`:
    - Busca todas as soluções com mesmo slug ou prefixo do nome da questão no respectivo ano e nível.

---

### Componente 3: Módulo de Descompactação Segura (`zip_extractor.py`)

Extração de arquivos com sanitização de caminhos contra Zip Slip e tratamento de arquivos corrompidos.

#### [NEW] [`src/processor/zip_extractor.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/processor/zip_extractor.py)
- Classe `ZipExtractor`:
  - `extract_test_cases(zip_path: Path, target_dir: Path) -> bool`:
    - Valida integridade com `zipfile.is_zipfile`.
    - Utiliza diretório temporário para extração segura, prevenindo poluição de disco em caso de falhas parciais.
    - Proteção estrita contra Zip Slip (rejeição de caminhos com `..` ou absolutos).
    - Retorna `True` em caso de sucesso e `False` (registrando em log) se o arquivo estiver corrompido (`zipfile.BadZipFile`).
  - `extract_solutions(zip_path: Path, target_dir: Path) -> list[Path]`:
    - Extrai arquivos de soluções mantendo extensões válidas (`.c`, `.cpp`, `.py`, `.java`, etc.).

---

### Componente 4: Módulo de Normalização Sequencial (`normalizer.py`)

Identificação de pares biunívocos de teste e padronização numerada a partir de 1.

#### [NEW] [`src/processor/normalizer.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/processor/normalizer.py)
- Classe `TestCaseNormalizer`:
  - `scan_and_pair(raw_dir: Path) -> list[tuple[Path, Path]]`:
    - Identifica todos os candidatos a arquivos de entrada (`.in`) e saída (`.out`, `.sol`).
    - Resolve múltiplos padrões estruturais encontrados nas provas da OBI:
      - Arquivos em subpastas numeradas `1/in` e `1/out`.
      - Arquivos no mesmo diretório com mesmo prefixo/stem: `teste1.in` e `teste1.out`, `in1` e `out1`.
      - Arquivos pareados por ordenação numérica ou alfanumérica consistente.
    - Garante correlação biunívoca estrita 1-para-1 (Invariante I2). Entradas sem saída ou saídas sem entrada são rejeitadas.
  - `normalize_to_destination(pairs: list[tuple[Path, Path]], test_cases_dir: Path) -> list[TestCasePair]`:
    - Cria `test_cases_dir / "inputs"` e `test_cases_dir / "outputs"`.
    - Ordena os pares por índice numérico natural.
    - Renomeia sequencialmente para `1.in`, `1.out`, `2.in`, `2.out`, etc.
    - Retorna a lista estruturada de `TestCasePair`.

---

### Componente 5: Módulo de Limpeza e Expurgador (`cleaner.py`)

Higienização do diretório da questão e exclusão de questões que não possuam casos de teste.

#### [NEW] [`src/processor/cleaner.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/processor/cleaner.py)
- Classe `DatasetCleaner`:
  - `clean_test_cases_residuals(test_cases_dir: Path, valid_pairs: list[TestCasePair])`:
    - Varre `test_cases_dir` e remove qualquer arquivo compilado (`.exe`, `.o`), arquivos temporários, subdiretórios vazios ou arquivos estranhos (Regra R5).
  - `validate_and_cleanup_question(question_path: Path, has_valid_tests: bool) -> bool`:
    - Se `has_valid_tests` for `False` ou `test_cases/` estiver vazio:
      - Remove completamente o diretório da questão (`shutil.rmtree`), cumprindo Regra R7, Exemplo E3 e Invariante I4.
      - Retorna `False` (questão descartada).
    - Se possuir testes válidos:
      - Assegura preservação intocada de `problem.json` e `imgs/` (Invariante I1).
      - Retorna `True` (questão mantida).

---

### Componente 6: Orquestrador Central (`questions_organizer.py`)

Coordenação do fluxo completo por questão e em lote com auditoria.

#### [NEW] [`src/processor/questions_organizer.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/processor/questions_organizer.py)
- Classe `QuestionsOrganizer`:
  - `discover_questions(output_dir: Path, ano_filtro: Optional[int], nivel_filtro: Optional[str]) -> list[QuestionFolder]`:
    - Varre `output_dir` procurando pastas contendo `problem.json`.
    - Lê metadados essenciais (`year` / `ano`, `level` / `nivel`, `title` / `titulo`).
    - Filtra por escopo se solicitado.
  - `organize_question(question: QuestionFolder, config: OrganizeConfig) -> OrganizeResult`:
    - 1. Verificação de idempotência: se `test_cases/` já tiver testes normalizados e `force=False`, pula (Regra R3).
    - 2. Busca gabarito correspondente via `ResourceMatcher` (Regra R1).
    - 3. Se houver gabarito ZIP: descompacta via `ZipExtractor` (Regras R2, R8).
    - 4. Normaliza pares de teste via `TestCaseNormalizer` (Regra R4, Invariante I2).
    - 5. Limpa resíduos via `DatasetCleaner` (Regra R5).
    - 6. Busca e copia/extrai soluções oficiais para `solutions/` (Regra R6, Invariante I3).
    - 7. Se não houver testes válidos: expurga pasta via `DatasetCleaner` (Regra R7, Invariante I4).
    - 8. Retorna `OrganizeResult` com resumo do processamento.
  - `organize_all(config: OrganizeConfig, ano_filtro: Optional[int], nivel_filtro: Optional[str]) -> dict[str, Any]`:
    - Executa o pipeline para todas as questões mapeadas e retorna sumário estatístico completo.

#### [NEW] [`src/processor/__init__.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/processor/__init__.py)
- Exporta `QuestionsOrganizer`, `ResourceMatcher`, `ZipExtractor`, `TestCaseNormalizer`, `DatasetCleaner`.

---

### Componente 7: Ponto de Entrada CLI (`main.py`)

Integração no CLI central do repositório substituindo código legado monolítico.

#### [MODIFY] [`main.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/main.py)
- Atualizar parser de argumentos:
  - Adicionar opção `organize-questions` na lista de `--step` (mantendo `organize-testcases` como alias plenamente suportado).
- Substituir as funções legadas `organizar_test_cases()`, `limpar_pastas_test_cases()`, `limpar_test_cases()` e `remover_questoes_sem_testes()` pela chamada limpa ao `QuestionsOrganizer`.
- Repassar parâmetros `--ano`, `--nivel` e `--force`.

---

## 4. Checklist de Execução por Tasks (Commits Atômicos)

Conforme a diretriz da skill `plans`, a execução ocorrerá na branch `feat/organize-questions` criada a partir de `main`:

### [x] Task 1: Criação da Branch e Modelos de Domínio (`test_case.py`)
- Criar a branch de trabalho `feat/organize-questions` a partir de `main`.
- Adicionar constantes em `src/core/config.py`.
- Implementar as entidades dataclass em `src/models/test_case.py` e exportá-las em `src/models/__init__.py`.
- Criar testes unitários em `tests/unit/test_models_test_case.py` cobrindo instanciação e validações.
- **Commit:** `e32a3e18 feat(models): define test case and question organization models`

### [x] Task 2 (TDD): Módulo de Normalização e Correspondência (`matcher.py`)
- Criar suite de testes em `tests/unit/test_matcher.py`:
  - Normalização estrita NFD: remoção de acentos, pontuações e case-folding.
  - Correspondência exata por ano/nível/slug.
  - Correspondência resiliente com títulos com variações ortográficas e hífens.
  - Descoberta e associação de soluções oficiais (`c`, `cpp`, `py`, `java`, etc.).
- Implementar `src/processor/matcher.py`.
- Executar testes até 100% de aprovação.
- **Commit:** `88e67269 feat(processor): implement unicode name normalization and resource matcher with unit tests`

### [x] Task 3 (TDD): Módulo de Descompactação Segura (`zip_extractor.py`)
- Criar suite de testes em `tests/unit/test_zip_extractor.py`:
  - Descompactação de ZIP válido de gabarito para diretório temporário.
  - Proteção contra Zip Slip (caminhos inseguros).
  - Tratamento resiliente de ZIP corrompido ou arquivo truncado sem gerar exceção não tratada.
  - Extração de ZIPs de código de solução.
- Implementar `src/processor/zip_extractor.py`.
- Executar testes até 100% de aprovação.
- **Commit:** `b03d7efa feat(processor): implement safe zip extractor with zip slip protection and resilience`

### [x] Task 4 (TDD): Módulo de Normalização de Pares de Teste (`normalizer.py`)
- Criar suite de testes em `tests/unit/test_normalizer.py`:
  - Detecção de pares `.in` e `.out` / `.sol` em múltiplos formatos de gabarito da OBI.
  - Ordenação natural e renumeração sequencial base 1 (`1.in`, `1.out`, `2.in`, `2.out`, etc.).
  - Rejeição de arquivos de entrada ou saída órfãos (garantia da Invariante I2).
  - Alocação em `inputs/` e `outputs/`.
- Implementar `src/processor/normalizer.py`.
- Executar testes até 100% de aprovação.
- **Commit:** `ec6f2fd5 feat(processor): implement test cases pair detection and 1-based sequential normalizer`

### [x] Task 5 (TDD): Módulo de Limpeza e Expurgador (`cleaner.py`)
- Criar suite de testes em `tests/unit/test_cleaner.py`:
  - Expurgo de arquivos compilados `.exe`, `.o` e arquivos de log residuais de `test_cases/`.
  - Remoção completa de diretórios de questões sem casos de teste válidos.
  - Preservação estrita de `problem.json` e `imgs/` para questões com testes válidos (Invariante I1).
- Implementar `src/processor/cleaner.py`.
- Executar testes até 100% de aprovação.
- **Commit:** `b6d957fa feat(processor): implement dataset cleaner and invalid question expurgation`

### [x] Task 6 (TDD): Orquestrador Central (`questions_organizer.py`)
- Criar suite de testes em `tests/unit/test_questions_organizer.py`:
  - Descoberta e leitura de pastas de questões com `problem.json`.
  - Comportamento idempotente quando testes válidos já existem (`force=False`).
  - Reprocessamento forçado com `force=True`.
  - Isolamento físico entre `test_cases/` e `solutions/` (Invariante I3).
  - Geração de relatório de resultados (`OrganizeResult`).
- Implementar `src/processor/questions_organizer.py` e `src/processor/__init__.py`.
- Executar testes até 100% de aprovação.
- **Commit:** `4b5d58e2 feat(processor): implement QuestionsOrganizer coordinator with full pipeline support`

### [x] Task 7: Integração no CLI (`main.py`) e Testes de CLI
- Atualizar `main.py` com o novo step `organize-questions` e alias `organize-testcases`.
- Atualizar `tests/unit/test_cli.py` com testes para o novo step, filtros `--ano`, `--nivel` e `--force`.
- Garantir que a suíte completa passe sem regressões: `uv run pytest`.
- **Commit:** `6405a09b feat(cli): integrate QuestionsOrganizer into main CLI and update cli tests`

### [x] Task 8: Validação Prática, Documentação e Abertura de Pull Request
- Executar teste prático com dados reais do dataset (ex: `--step organize-questions --ano 2024 --nivel pj`).
- Atualizar checklist deste plano com os status e commits.
- Abrir Pull Request de `feat/organize-questions` para `main` documentando todas as alterações.
- **Commit:** `docs(plans): mark organize-questions-plan as completed`


---

## 5. Estratégia de Testes e Validação (TDD)

### Testes Automatizados Unitários
- `tests/unit/test_models_test_case.py`: Cobertura de integridade dos tipos e defaults.
- `tests/unit/test_matcher.py`: Testes com strings complexas com acentuação ("Cabo de Guerra", "Aviões de Papel", "Pão a Queijo").
- `tests/unit/test_zip_extractor.py`: Testes com arquivos zip gerados em tempo de teste e simulação de arquivos corrompidos.
- `tests/unit/test_normalizer.py`: Testes com estruturas de gabaritos OBI (pastas `1/in`, `1/out`, arquivos `in1`/`out1`, etc.).
- `tests/unit/test_cleaner.py`: Verificação de remoção de arquivos e integridade de `problem.json`.
- `tests/unit/test_questions_organizer.py`: Teste de integração do orquestrador com mocks e fixtures de diretórios temporários (`tmp_path`).
- `tests/unit/test_cli.py`: Verificação do parsing e acionamento correto dos argumentos do CLI.

Comando de execução completa:
```bash
uv run pytest -v
```

### Validação Manual e Prática
- Executar:
  ```bash
  uv run main.py --step organize-questions --ano 2023 --nivel pj
  ```
- Inspecionar as pastas de saída para confirmar:
  - Presença de `test_cases/inputs/` e `test_cases/outputs/` com `1.in`, `1.out`, etc.
  - Presença de `solutions/` com arquivos de código oficiais.
  - Inexistência de arquivos `.exe`, `.o` ou pastas vazias.
  - Integridade de `problem.json`.
  - Idempotência em reexecução sem `--force`.

---

## 6. Critérios de Aceite

1. Todos os novos módulos implementados residem estritamente em `src/processor/` e `src/models/` seguindo Clean Architecture.
2. Correspondência de questões, gabaritos e códigos funciona com normalização Unicode NFD estrita.
3. Casos de teste são numerados sequencialmente a partir de 1 em pares `[numero].in` e `[numero].out` (Invariante I2).
4. Casos de teste e códigos de solução residem isoladamente em `test_cases/` e `solutions/` (Invariante I3).
5. O arquivo `problem.json` e imagens em `imgs/` nunca são corrompidos ou apagados em questões válidas (Invariante I1).
6. Nenhuma questão sem casos de teste válidos permanece na base consolidada após a execução (Invariante I4).
7. O CLI responde a `--step organize-questions` e ao alias `--step organize-testcases`.
8. 100% de aprovação na suíte de testes com `uv run pytest`.
9. Ausência total de emojis em código, documentação, commits e mensagens.
