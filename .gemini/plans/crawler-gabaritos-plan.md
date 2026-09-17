# PLANO DE IMPLEMENTACAO: Crawler de Gabaritos e Casos de Teste (ZIP) - v0.1

- **Identificador:** `crawler-gabaritos-plan`
- **Especificacao:** [`.gemini/specs/spec-crawler-gabaritos.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-crawler-gabaritos.md)
- **Branch de Trabalho:** `feat/crawler-gabaritos` (criada a partir de `main`)
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md), [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md)

---

## 1. Visao Geral e Alinhamento com a Spec

Implementar de forma modular, desacoplada, resiliente e orientada a testes o modulo de busca e download de gabaritos e casos de teste compactados (.zip) da OBI, atendendo integralmente as regras da especificacao:
1. **Identificacao Abrangente de Gabaritos (R1):** Identificar links que terminam em `.zip` e contenham os termos `gabarito` ou `testes` no texto visivel do link ou no endereco URL (`href`).
2. **Denominacao Padronizada (R2):** Utilizar o texto visivel do link (sanitizado) como nome do arquivo final (ex: `Entrevistas de Emprego.zip`); caso esteja vazio ou ausente, utilizar o nome original do arquivo extraido da URL.
3. **Sanitizacao de Nomes (R3, I2):** Remover estritamente caracteres proibidos para sistemas de arquivos (`\ / : * ? " < > |`), evitando falhas de I/O em ambientes Windows e Linux.
4. **Idempotencia Rigorosa (R4, E2):** Se o arquivo `.zip` ja existir localmente ou estiver registrado no manifesto (`.manifest.json`), pular a requisicao de download e contabilizar como ja existente.
5. **Integridade de Arquivos ZIP (R5, I1):** Validar se o arquivo baixado e um ZIP valido e nao vazio (`zipfile.is_zipfile`). Se corrompido, vazio ou interrompido, excluir imediatamente qualquer residuo em disco e registrar erro no log.
6. **Respeito ao Servidor da OBI (R6):** Pausa minima configuravel de 0.5s entre downloads consecutivos e politica de conexao com retries e backoff exponencial via `HttpClient`.
7. **Isolamento de Diretorio:** Destinar os arquivos exclusivamente a estrutura `gabaritos/[ano]/[nivel]/[nome_arquivo].zip`, sem misturar com cadernos de questoes (`cadernos/`) ou codigos-fonte (`codigo/`).
8. **Integracao no CLI:** Substituir a funcao monolítica legada de `main.py` pelo novo orquestrador modular `GabaritosDownloader`, com suporte a filtros `--ano` e `--nivel`, alem de flag `--force`.

---

## 2. Modelagem de Dados e Entidades

### `GabaritoZIP`
```python
@dataclass(frozen=True)
class GabaritoZIP:
    ano: int
    nivel: str
    nome_questao: str
    url: str
    caminho_local: Optional[Path] = None
    texto_link: str = ""
```

### `GabaritoCrawlerConfig`
```python
@dataclass(frozen=True)
class GabaritoCrawlerConfig:
    pasta_base: Path = Path("gabaritos")
    timeout: int = 15
    delay_requests: float = 0.5
    termos_filtro: tuple[str, ...] = ("gabarito", "testes")
```

---

## 3. Modulos Afetados e Estrutura de Arquivos

```text
problems-of-the-obi/
├── .gemini/
│   ├── plans/
│   │   └── crawler-gabaritos-plan.md     # Este documento de planejamento
│   ├── prompts/
│   │   └── 016-criar-plano-crawler-gabaritos.md
│   └── specs/
│       └── spec-crawler-gabaritos.md     # Especificacao funcional de referencia
├── src/
│   ├── core/
│   │   └── config.py                     # Constantes de gabaritos e classe GabaritoCrawlerConfig
│   └── crawler/
│       ├── scraper.py                    # Entidade GabaritoZIP e metodo extract_gabarito_links
│       └── gabaritos_downloader.py       # Orquestrador GabaritosDownloader com idempotencia e validacao ZIP
├── tests/
│   └── unit/
│       ├── test_scraper_gabaritos.py     # Testes de extracao de links de gabarito e inferencia
│       └── test_gabaritos_downloader.py  # Testes de download, integridade de ZIP e idempotencia
└── main.py                               # Substituicao do metodo legado por GabaritosDownloader no CLI
```

---

## 4. Checklist de Execucao por Tasks (Commits Atomicos)

Conforme a diretriz da skill `plans`, a execucao ocorrera na branch `feat/crawler-gabaritos` com commits atomicos individuais por tarefa:

### [x] Task 1: Criacao da Branch e Modelos de Configuracao e Entidades
- Criar a branch `feat/crawler-gabaritos` a partir de `main`.
- Adicionar constantes em `src/core/config.py`: `TERMOS_GABARITO = ("gabarito", "testes")` e dataclass `GabaritoCrawlerConfig`.
- Definir dataclass `GabaritoZIP` em `src/crawler/scraper.py`.
- **Commit:** `2b0e8bd1 feat(crawler): setup branch and define gabarito crawler configuration models`

### [x] Task 2 (TDD): Extracao de Links de Gabarito no `ObiScraper`
- Criar suite de testes em `tests/unit/test_scraper_gabaritos.py`:
  - Reconhecimento de links `.zip` com termo `gabarito` ou `testes` no `href` ou no texto visivel.
  - Descarte de arquivos que nao sejam `.zip` ou que nao contenham os termos de gabarito.
  - Descarte de links que apontam para solucoes de codigo quando nao forem gabaritos de teste.
  - Extracao correta do nome da questao a partir do texto visivel ou do nome do arquivo na URL.
  - Inferencia precisa do nivel (`pj`, `p1`, `p2`, `senior`, `geral`).
  - Resolucao de URLs relativas para absolutas.
- Implementar `extract_gabarito_links` no `ObiScraper` em `src/crawler/scraper.py`.
- Executar `uv run pytest tests/unit/test_scraper_gabaritos.py` ate 100% de aprovacao.
- **Commit:** `f8b9226b feat(crawler): implement gabarito links extraction in ObiScraper with unit tests`

### [x] Task 3 (TDD): Downloader Idempotente e Resiliente de Gabaritos (`GabaritosDownloader`)
- Criar suite de testes em `tests/unit/test_gabaritos_downloader.py`:
  - Sanitizacao de nomes de arquivo (remocao de `\ / : * ? " < > |`).
  - Resolucao correta de caminho local: `gabaritos/[ano]/[nivel]/[nome_sanitizado].zip`.
  - Idempotencia (R4): arquivo existente em disco ou no manifest `.manifest.json` pula download de rede.
  - Validacao de integridade (R5, I1): download de arquivo invalido ou corrompido remove o arquivo temporario/residual e nao corrompe o destino.
  - Flag `force=True` forca novo download mesmo se ja existente.
  - Persistencia de mapeamento no `.manifest.json`.
- Implementar `GabaritosDownloader` em `src/crawler/gabaritos_downloader.py`.
- Executar `uv run pytest tests/unit/test_gabaritos_downloader.py` ate 100% de aprovacao.
- **Commit:** `dd025839 feat(crawler): implement idempotent GabaritosDownloader with ZIP integrity validation`

### [x] Task 4: Integracao no CLI (`main.py`)
- Refatorar a chamada da etapa `--step download-gabaritos` em `main.py` para utilizar `GabaritosDownloader`.
- Suportar filtros de escopo `--ano` e `--nivel`, alem da flag `--force`.
- Atualizar `tests/unit/test_cli.py` para cobrir o acionamento do step `download-gabaritos`.
- **Commit:** `a5d80131 feat(cli): integrate modular GabaritosDownloader into main CLI`

### [x] Task 5: Validacao da Suite Completa e Execucao Pratica
- Executar a suite completa de testes: `uv run pytest -v` (garantindo zero regressoes em cadernos, codigos, scrapers e gabaritos: 53 testes aprovados).
- Executar teste pratico controlado: `uv run main.py --step download-gabaritos --ano 2023 --nivel pj`.
- Validar criacao correta da arvore de diretorios `gabaritos/2023/pj/` com 13 arquivos `.zip` validos e nao corrompidos.
- Validar idempotencia em reexecucao consecutiva (13 encontrados, 0 baixados, 13 ja existentes).
- **Commit:** `a7c460c1 test(crawler): verify full test suite and validate gabaritos downloader execution`

### [x] Task 6: Documentacao, Finalizacao e Abertura de Pull Request
- Atualizar checklist em `.gemini/plans/crawler-gabaritos-plan.md` com status de conclusao e hashes dos commits.
- Atualizar tabela de consumo de tokens em `.gemini/prompts/016-criar-plano-crawler-gabaritos.md`.
- Abrir Pull Request a partir de `feat/crawler-gabaritos` para `main` com o sumario de alteracoes.
- **Commit:** `docs(plans): mark crawler-gabaritos-plan as completed`

---

## 5. Criterios de Aceite

1. Todos os arquivos de gabarito e casos de teste sao salvos exclusivamente sob `gabaritos/[ano]/[nivel]/[nome_sanitizado].zip`.
2. O nome do arquivo salvo preserva o titulo visivel da questao sanitizado; na ausencia de texto, utiliza o stem do arquivo original.
3. Caracteres invalidos em sistemas de arquivos (`\ / : * ? " < > |`) sao eliminados sem gerar excecoes de I/O.
4. Somente arquivos ZIP integros e nao vazios sao mantidos no diretorio final; arquivos truncados ou corrompidos sao descartados (Invariante I1).
5. Execucoes consecutivas sao 100% idempotentes, pulando arquivos ja existentes ou registrados no manifesto (Regra R4).
6. Respeito ao intervalo minimo de requisicoes de 0.5s entre downloads (Regra R6).
7. Ausencia absoluta de emojis em logs de console, comentarios de codigo, documentacao e commits.
8. Aprovacao de 100% dos testes unitarios via `uv run pytest`.
