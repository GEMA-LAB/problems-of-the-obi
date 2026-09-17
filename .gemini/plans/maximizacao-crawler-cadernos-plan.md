# PLANO DE IMPLEMENTACAO: Maximizacao e Resiliencia do Crawler de Cadernos (PDF)

- **Identificador:** `maximizacao-crawler-cadernos-plan`
- **Especificacao:** [`.gemini/specs/spec-crawler-cadernos.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-crawler-cadernos.md)
- **Branch de Trabalho:** `feat/crawler-cadernos`
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md), [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md)

---

## 1. Diagnostico das Execucoes Anteriores

### 1.1. Discrepancia entre Execucao 1 (172 PDFs) e Execucao 2 (144 PDFs)
A diferenca exata observada de **28 PDFs** (172 - 144) foi investigada e isolada nos arquivos em disco e no manifest:
- **Causa Raiz:** Durante a execucao 2, as requisicoes para a **Fase 3** de 7 anos (**2017, 2019, 2020, 2021, 2022, 2023 e 2025**) falharam silenciosamente ou nao foram computadas (7 anos x 4 niveis = 28 PDFs).
- **Evidencia:** Apenas o ano 2024 teve a Fase 3 baixada no primeiro lote (pois 2024 utiliza o sufixo `fase3/programacao/cadernos/`, enquanto os demais 7 anos utilizam `fase3/programacao/`).
- **Validacao:** Apos a execucao 2, o teste isolado com `--ano 2022` encontrou imediatamente 12 cadernos (8 ja existentes + os 4 da Fase 3 baixados com sucesso).

---

## 2. Oportunidades Identificadas para Maximizacao do Dataset

O universo de cadernos de programacao no servidor da Unicamp e consideravelmente maior que 172:

| Categoria / Ano | Quantidade | Situacao Atual no Crawler | Acao Proposta |
| :--- | :--- | :--- | :--- |
| **Ano 2018** | **12 PDFs** | Ignorado (pagina `/passadas/OBI2018/` retorna HTTP 404) | Probing direto em `static/extras/obi2018/provas/` |
| **Ano 2026** | **8 PDFs** | Fora do range (`END_YEAR=2026` exclusivo no `range()`) | Ajustar `END_YEAR=2027` e probing estatico |
| **CFOBI (Comp. Feminina)** | **9 PDFs** | Nao mapeado (anos 2023, 2024 e 2025) | Incluir padroes `cfobi/programacao/` e `cfobi/.../cadernos/` |
| **Provas B / Variacoes** | **4 PDFs** | Mapeado parcialmente (`programacaob`) | Garantir normalizacao completa de fases complementares |
| **Fase 3 dos 7 anos** | **28 PDFs** | Oscilacao / instabilidade de rede | Implementar retries com backoff e timeout resiliente |

- **Total maximo alcancavel na Modalidade Programacao:** **205 cadernos de questoes** (subindo de 144/172 para 205).
- *(Opcional)* **Modalidade Iniciacao:** Adiciona mais 75 cadernos de questoes (totalizando 280 cadernos).

---

## 3. Arquitetura Tecnica Proposta

1. **Camada de Probing Estatico de Fallback (`StaticProber`):**
   - Para anos conhecidos com index quebrado (2018) ou ano corrente (2026), sondar diretamente os nomes padronizados em `static/extras/obi{ano}/provas/ProvaOBI{ano}_{fase}{nivel}.pdf` via requisicoes `HEAD`.
2. **Descoberta Dinamica de Subpaginas por Ano:**
   - Em vez de depender apenas de lista fixa em `PADROES_CADERNOS`, ler a pagina raiz `OBI{ano}/` e coletar links internos de programacao e cfobi.
3. **Resiliencia no `HttpClient`:**
   - Adicionar retries automaticos (max 3 tentativas) com backoff exponencial para evitar perda de fases inteiras por instabilidade temporaria do servidor da Unicamp.
4. **Atualizacao de Constantes em `config.py`:**
   - `START_YEAR = 1999`, `END_YEAR = 2027`.
   - Inclusao de padroes `cfobi/programacao/` e `cfobi/programacao/cadernos/`.

---

## 4. Checklist de Execucao (TDD & Commits Atomicos)

- [ ] **Task 1 (TDD):** Testes unitarios para retries e fallback estatico no `HttpClient` e `CadernosDownloader`.
- [ ] **Task 2:** Implementar resiliencia com retries no `HttpClient`.
- [ ] **Task 3:** Adicionar suporte a `cfobi/`, ano 2018 (fallback estatico) e ano 2026 (`END_YEAR=2027`) em `config.py` e `downloader`.
- [ ] **Task 4:** Executar varredura completa e validar alcance de 205 cadernos de programacao.
- [ ] **Task 5:** Atualizar metricas e documentacao de status.
