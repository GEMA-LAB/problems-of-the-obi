# PLANO DE IMPLEMENTACAO: Crawler de Solucoes e Codigos-Fonte Oficiais - v0.1

- **Identificador:** `crawler-codigos-plan`
- **Especificacao:** [`.gemini/specs/spec-crawler-codigos.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-crawler-codigos.md)
- **Branch de Trabalho:** `feat/crawler-codigos` (criada a partir de `main`)
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md), [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md)

---

## 1. Visao Geral e Alinhamento com a Spec

Implementar de forma modular, resiliente e orientada a testes o modulo de download de codigos e solucoes oficiais disponibilizados pela OBI, atendendo integralmente as regras da especificacao:
1. **Descoberta Abrangente (R1):** Identificar links de programas de exemplo e solucoes oficiais disponibilizados nas paginas de programacao da OBI em extensoes validas (`.c`, `.cpp`, `.py`, `.java`, `.pas`, `.js`, `.zip`).
2. **Idempotencia Rigorosa (R2):** Nao realizar download redundante caso o arquivo ja exista localmente ou ja tenha sido registrado no manifesto (`.manifest.json`).
3. **Sanitizacao e Prevencao de Colisoes (R3):** Sanitizar nomes de arquivos e prefixar com o nome do problema para evitar que solucoes homonimas de autores comuns (como `andre.cpp` ou `lucchesi.c`) colidam dentro do mesmo ano/nivel.
4. **Respeito ao Servidor da OBI (R4):** Pausa minima configuravel de 0.5s entre downloads consecutivos e politica de retries com backoff via `HttpClient`.
5. **Isolamento e Invariante (I1):** Arquivos salvos exclusivamente sob `codigo/[ano]/[nivel]/[nome_arquivo]`, sem misturar com cadernos de provas (`cadernos/`) ou casos de teste (`gabaritos/`).
6. **Integracao no CLI:** Suporte ao comando `uv run main.py --step download-codigos` com filtros opcionais de `--ano` e `--nivel`.

---

## 2. Modelagem de Dados e Entidades

### `CodigoSolucao`
```python
@dataclass(frozen=True)
class CodigoSolucao:
    ano: int
    nivel: str
    nome_problema: str
    linguagem: str  # 'c', 'cpp', 'py', 'java', 'js', 'pas', 'zip'
    url: str
    nome_arquivo: str
    caminho_local: Path  # codigo/[ano]/[nivel]/[nome_arquivo]
```

### `CodigoCrawlerConfig`
```python
@dataclass(frozen=True)
class CodigoCrawlerConfig:
    pasta_base: Path = Path("codigo")
    timeout: int = 15
    delay_requests: float = 0.5
    extensoes_validas: tuple[str, ...] = (
        ".c", ".cpp", ".py", ".java", ".pas", ".js", ".zip"
    )
```

---

## 3. Módulos Afetados e Estrutura de Arquivos

```text
problems-of-the-obi/
├── .gemini/
│   ├── plans/
│   │   └── crawler-codigos-plan.md     # Este documento de planejamento
│   └── prompts/
│       └── 012-criar-plano-crawler-codigos.md
├── src/
│   ├── core/
│   │   └── config.py                   # Constantes de extensoes e configuracoes de codigo
│   └── crawler/
│       ├── scraper.py                  # Adicao de extract_code_links e infer_solution_metadata
│       └── codigos_downloader.py       # Orquestrador CodigosDownloader com idempotencia e manifest
├── tests/
│   └── unit/
│       ├── test_scraper_codigos.py     # Testes de extracao de links de solucoes e parsing
│       └── test_codigos_downloader.py  # Testes de download, idempotencia e colisao
└── main.py                             # Adicao do step download-codigos no CLI
```

---

## 4. Checklist de Execucao por Tasks (Commits Atomicos)

Conforme a diretiva da skill `plans`, a execucao ocorrera na branch `feat/crawler-codigos` com commits atomicos individuais por tarefa:

### [ ] Task 1: Criacao da Branch e Estrutura de Configuracao
- Criar a branch `feat/crawler-codigos` a partir de `main`.
- Adicionar constantes em `src/core/config.py` (`EXTENSOES_CODIGO`, `MAPEAMENTO_LINGUAGEM`).
- Definir dataclasses `CodigoSolucao` e `CodigoCrawlerConfig`.
- **Commit:** `feat(crawler): setup branch and define code crawler configuration models`

### [ ] Task 2 (TDD): Extracao de Links de Codigo no `ObiScraper`
- Criar testes unitarios em `tests/unit/test_scraper_codigos.py`:
  - Reconhecimento de links com extensoes validas (`.c`, `.cpp`, `.py`, `.py3`, `.java`, `.js`, `.pas`).
  - Extracao correta do nome do problema a partir da URL (ex: `2022f1pj_cinema -> cinema`).
  - Deducao da linguagem com base na extensao.
  - Ignorar links que pertencem a gabaritos de teste (`/gabaritos/`, `.zip` de testes).
- Implementar `extract_code_links` e metodos auxiliares em `src/crawler/scraper.py`.
- Rodar `uv run pytest tests/unit/test_scraper_codigos.py` ate 100% de aprovacao.
- **Commit:** `feat(crawler): implement code solution links scraper with unit tests`

### [ ] Task 3 (TDD): Downloader Idempotente de Codigos (`CodigosDownloader`)
- Criar testes unitarios em `tests/unit/test_codigos_downloader.py`:
  - Download bem-sucedido de codigo em `codigo/[ano]/[nivel]/[nome_arquivo]`.
  - Idempotencia: arquivo ja existente ou registrado em `.manifest.json` nao realiza requisicao de rede.
  - Resolucao de colisao: renomeacao adequada quando o arquivo original for generico (ex: `andre.cpp -> cinema_andre.cpp`).
  - Persistencia de URL no `.manifest.json`.
  - Tratamento gracioso de erros de rede ou status HTTP diferente de 200.
- Implementar `CodigosDownloader` em `src/crawler/codigos_downloader.py`.
- Rodar `uv run pytest tests/unit/test_codigos_downloader.py` ate 100% de aprovacao.
- **Commit:** `feat(crawler): implement idempotent code downloader with manifest and collision resolution`

### [ ] Task 4: Integracao no CLI (`main.py`)
- Atualizar `main.py` para suportar `uv run main.py --step download-codigos`.
- Suporte aos filtros `--ano` e `--nivel`.
- Adicionar teste unitario de CLI em `tests/unit/test_cli.py` para o novo step.
- **Commit:** `feat(cli): integrate download-codigos step into main CLI`

### [ ] Task 5: Validacao da Suite Completa e Execucao Pratica
- Executar suite completa de testes: `uv run pytest -v` (garantindo 0 regressoes e 100% de testes aprovados).
- Executar validacao pratica controlada: `uv run main.py --step download-codigos --ano 2022 --nivel pj`.
- Validar se os codigos foram salvos corretamente em `codigo/2022/pj/` com nomes sanitizados e sem emojis no terminal.
- **Commit:** `test(crawler): verify full test suite and validate code crawler execution`

### [ ] Task 6: Abertura do Pull Request
- Enviar branch remota: `git push -u origin feat/crawler-codigos`.
- Abrir Pull Request com descricao detalhada das alteracoes e vinculo a `spec-crawler-codigos.md`.
- **Commit:** `docs(plans): mark crawler-codigos-plan as completed`

---

## 5. Criterios de Aceite
1. Todos os codigos sao salvos exclusivamente sob `codigo/[ano]/[nivel]/[nome_arquivo]`.
2. Nenhuma solucao oficial sobrescreve ou colide com outra devido a homonimos de autores.
3. Execucoes consecutivas sao 100% idempotentes (0 downloads redundantes).
4. Suporte a todas as linguagens da especificacao (`c`, `cpp`, `py`, `java`, `js`, `pas`, `zip`).
5. Zero uso de emojis em logs, commits e documentacao.
6. 100% dos testes unitarios passam com `uv run pytest`.
