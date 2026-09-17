# Prompt 010 - Discrepancia na Quantidade de Cadernos Encontrados e Maximizacao

- **Data e Hora:** 2026-09-17 12:24:20 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
(.venv) PS C:\Users\Victo\Desktop\Ufal\problems-of-the-obi> uv run .\main.py --step download-cadernos

🚀 INICIANDO PIPELINE DE AUTOMAÇÃO DA OBI 🚀


========================================
1. DOWNLOAD DOS CADERNOS (PDFs)
========================================
Estatísticas dos Cadernos: {'encontrados': 172, 'baixados': 171, 'ja_existentes': 0, 'falhas': 1}

🎉 ETAPA DOWNLOAD-CADERNOS FINALIZADA! 🎉
(.venv) PS C:\Users\Victo\Desktop\Ufal\problems-of-the-obi> uv run .\main.py --step download-cadernos

INICIANDO PIPELINE DE AUTOMACAO DA OBI


========================================
1. DOWNLOAD DOS CADERNOS (PDFs)
========================================
Estatisticas dos Cadernos: {'encontrados': 144, 'baixados': 144, 'ja_existentes': 0, 'falhas': 0}

ETAPA DOWNLOAD-CADERNOS FINALIZADA COM SUCESSO.

Veja as execuções acima e porque menos pdfs foram encontrados? Quero maximar isso.
```

---

## Diagnóstico Técnico e Resumo das Descobertas

1. **Causa da Discrepância (172 vs 144):**
   - A diferença exata é de 28 cadernos, correspondentes à Fase 3 de 7 anos (2017, 2019, 2020, 2021, 2022, 2023 e 2025).
   - Apenas o ano de 2024 teve a Fase 3 coletada na 2ª execução (`fase3/programacao/cadernos/`).
   - Nos outros 7 anos, a rota é `fase3/programacao/`. As requisições sofreram timeout ou instabilidade transitória de rede e foram descartadas silenciosamente pela falta de retries no `HttpClient`.

2. **Oportunidades de Maximização Identificadas:**
   - **Ano 2018 (12 PDFs):** Página índice `/passadas/OBI2018/` retorna HTTP 404, mas os arquivos existem no servidor estático (`/static/extras/obi2018/provas/`).
   - **Ano 2026 (8 PDFs):** `END_YEAR = 2026` com `range()` excluía o ano corrente, cujos cadernos de Fase 1 e 2 já estão disponíveis.
   - **CFOBI (9 PDFs):** Provas oficiais de programação da Competição Feminina (2023 a 2025).
   - **Provas complementares (B e 2B):** Suporte adicionado via `programacaob`.
   - **Teto da Modalidade Programação:** **205 cadernos de questões**.

3. **Plano de Implementação Gerado:**
   - Registrado em `.gemini/plans/maximizacao-crawler-cadernos-plan.md`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **8.412.500** |
| ↳ *Input sem cache* | 485.200 |
| ↳ *Input em cache (Prompt Cache)* | 7.927.300 |
| **Output Tokens (Total)** | **14.200** |
| ↳ *Thinking / Raciocínio* | 6.850 |
| ↳ *Respostas / Chamadas de Ferramenta* | 7.350 |
| **Total Geral (Input + Output)** | **8.426.700** |
| **Iterações / Chamadas ao Modelo** | 28 |
