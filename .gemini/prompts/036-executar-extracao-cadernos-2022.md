# Prompt 036 - Execução da Extração Fiel dos Cadernos OBI 2022

- **Data e Hora:** 2026-09-18 20:31:06 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Agora é apenas repetição do plano para o ano de 2022 com alta fidelidade aos pdfs. Lembre sempre de salvar o prompt com as metricas.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Execução da Extração para o Ano de 2022:**
   - Mapeamento e inspeção de todos os cadernos PDF em `cadernos/2022/`.
   - Extração fiel dos enunciados, restrições, entradas, saídas e exemplos de teste.
   - Normalização e validação dos dados segundo o `ProblemSchema`.
   - Gravação dos arquivos `problem.json` em `output_with_code/2022/[nivel]/[nome da questão]/`.
   - Execução do organizador de testes/soluções e validação com `uv run pytest`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade |
| :--- | :--- |
| **Tokens de Entrada (sem cache)** | 420.466 |
| **Tokens de Entrada (cache)** | 4.064.637 |
| **Total de Tokens de Entrada** | 4.485.103 |
| **Tokens de Saída (Thinking)** | 16.159 |
| **Tokens de Saída (Resposta)** | 0 |
| **Total de Tokens de Saída** | 16.159 |
| **Total Geral de Tokens** | 4.501.262 |
| **Total de Iterações / Chamadas** | 44 |

---

## Resultados da Execução

- **Total de PDFs Processados:** 12 cadernos da OBI 2022 (`pj`, `p1`, `p2`, `senior` para as 3 fases).
- **Problemas Extraídos:** 46 problemas (`pj`: 10, `p1`: 10, `p2`: 13, `senior`: 13).
- **Integração de Testes e Soluções:** `uv run python main.py --step organize-questions --ano 2022` integrou 1.415 casos de teste e 170 códigos de soluções oficiais.
- **Validação de Testes Unitários:** 111 testes aprovados com sucesso via `uv run pytest`.

