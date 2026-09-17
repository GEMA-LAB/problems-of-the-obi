# PLANO DE IMPLEMENTACAO: Crawler de Cadernos de Provas (PDF) - v0.2

- **Identificador:** `crawler-cadernos-plan`
- **Especificacao:** [`.gemini/specs/spec-crawler-cadernos.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-crawler-cadernos.md)
- **Branch de Trabalho:** `feat/crawler-cadernos`
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md), [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md)

---

## 1. Contexto e Motivacao da Refatoracao (Regra R6)
Ao executar o download em edicoes da OBI que possuem fases complementares (ex: Fase 1B, Fase 2B ou provas B), arquivos homonimos (como `caderno.pdf` ou `prova_pj.pdf`) estavam sendo descartados pela verificacao de existencia previa.

A nova regra R6 da especificacao determina:
> **R6:** Se o arquivo PDF ja existir em disco e for proveniente de uma nova URL/execucao, o crawler deve salva-lo como `[nome]-[numero].pdf` (onde `numero` e o indice sequencial da execucao, ex: `caderno-1.pdf`, `caderno-2.pdf`), garantindo que nenhuma prova de fase B seja descartada.

---

## 2. Solucao Tecnica e Arquitetura

1. **Manifest de Idempotencia (`.manifest.json`):**
   - Para diferenciar uma reexecucao (onde o mesmo arquivo da mesma URL nao deve ser baixado de novo) de uma colisao de fase B (onde a mesma pasta contem arquivos homonimos de URLs diferentes), o `CadernosDownloader` mantera um registro em `cadernos/.manifest.json` mapeando `url -> caminho_relativo`.
2. **Algoritmo de Resolucao de Sufixo Numerado:**
   - Se `url` ja estiver no manifest e o arquivo existir -> pular download (idempotencia).
   - Se `url` for nova e o caminho `[nome].pdf` ja existir -> gerar `[nome]-1.pdf`, `[nome]-2.pdf`, etc., ate encontrar um caminho livre.
   - Apos download bem-sucedido, persistir a associacao no manifest.

---

## 3. Checklist de Execucao por Tasks (Commits Atomicos)

### [x] Task 1: Atualizacao do Plano com a Regra R6
- Documentar a regra R6 e a estrategia de manifest e sufixo numerado no plano.
- **Commit:** `docs(plans): update crawler-cadernos-plan with R6 collision resolution`

### [ ] Task 2 (TDD): Criacao de Testes para Colisao e Sufixo Numerado
- Criar testes unitarios em `tests/unit/test_cadernos_downloader.py`:
  - Teste simulando duas URLs distintas com mesmo nome de arquivo gerando `[nome].pdf` e `[nome]-1.pdf`.
  - Teste de idempotencia garantindo que reexecucoes das duas URLs nao criem `[nome]-2.pdf` indefinidamente.
  - Teste de integridade do arquivo `.manifest.json`.
- **Commit:** `test(crawler): add unit tests for R6 numbered suffix on file collisions`

### [ ] Task 3: Implementacao da Resolucao de Sufixo no Downloader
- Modificar `src/crawler/cadernos_downloader.py` para suportar `resolve_destination_path` com incremento numerico e gestao de manifest.
- Rodar `uv run pytest tests/unit/test_cadernos_downloader.py` ate 100% de aprovacao.
- **Commit:** `feat(crawler): implement numbered suffix resolution and download manifest`

### [ ] Task 4: Verificacao Completa da Suite de Testes
- Rodar `uv run pytest -v` garantindo zero regressoes em todos os testes unitarios.
- **Commit:** `chore(crawler): verify test suite passes with collision resolution`

### [ ] Task 5: Validacao Pratica do Download de Cadernos
- Executar `uv run python main.py --step download-cadernos` para constatar o download correto das provas de fases complementares.
- Registrar resultado no plano.
