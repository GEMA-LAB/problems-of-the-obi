# Prompt 037 - Execução da Extração Fiel dos Cadernos OBI 2021

- **Data e Hora:** 2026-09-18 20:42:29 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Agora é apenas repetição do plano para o ano de 2021 com alta fidelidade aos pdfs. Lembre sempre de salvar o prompt com as metricas.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Execução da Extração para o Ano de 2021:**
   - Mapeamento e inspeção de todos os cadernos PDF em `cadernos/2021/`.
   - Extração fiel dos enunciados, restrições, entradas, saídas e exemplos de teste.
   - Normalização e validação dos dados segundo o `ProblemSchema`.
   - Gravação dos arquivos `problem.json` em `output_with_code/2021/[nivel]/[nome da questão]/`.
   - Execução do organizador de testes/soluções e validação com `uv run pytest`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade |
| :--- | :--- |
| **Tokens de Entrada (sem cache)** | 420.086 |
| **Tokens de Entrada (cache)** | 2.168.699 |
| **Total de Tokens de Entrada** | 2.588.785 |
| **Tokens de Saída (Thinking)** | 10.364 |
| **Tokens de Saída (Resposta)** | 0 |
| **Total de Tokens de Saída** | 10.364 |
| **Total Geral de Tokens** | 2.599.149 |
| **Total de Iterações / Chamadas** | 35 |

---

## Resultados da Execução

- **Total de PDFs Processados:** 16 cadernos da OBI 2021 (`pj`, `p1`, `p2`, `senior` abrangendo as fases 1, 2, 2b e 3).
- **Problemas Extraídos:** 64 problemas (`pj`: 15, `p1`: 15, `p2`: 17, `senior`: 17).
- **Integração de Testes e Soluções:** `uv run python main.py --step organize-questions --ano 2021` integrou 1.546 casos de teste e 231 códigos de soluções oficiais.
- **Validação de Testes Unitários:** 111 testes aprovados com sucesso via `uv run pytest`.

