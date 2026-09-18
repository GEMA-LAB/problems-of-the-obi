# Prompt 038 - Execução da Extração Fiel dos Cadernos OBI 2020

- **Data e Hora:** 2026-09-18 20:47:59 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Agora é apenas repetição do plano para o ano de 2020 com alta fidelidade aos pdfs. Lembre sempre de salvar o prompt com as metricas.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Execução da Extração para o Ano de 2020:**
   - Mapeamento e inspeção de todos os cadernos PDF em `cadernos/2020/`.
   - Extração fiel dos enunciados, restrições, entradas, saídas e exemplos de teste.
   - Normalização e validação dos dados segundo o `ProblemSchema`.
   - Gravação dos arquivos `problem.json` em `output_with_code/2020/[nivel]/[nome da questão]/`.
   - Execução do organizador de testes/soluções e validação com `uv run pytest`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade |
| :--- | :--- |
| **Tokens de Entrada (sem cache)** | 132.749 |
| **Tokens de Entrada (cache)** | 2.908.543 |
| **Total de Tokens de Entrada** | 3.041.292 |
| **Tokens de Saída (Thinking)** | 8.630 |
| **Tokens de Saída (Resposta)** | 0 |
| **Total de Tokens de Saída** | 8.630 |
| **Total Geral de Tokens** | 3.049.922 |
| **Total de Iterações / Chamadas** | 27 |

---

## Resultados da Execução

- **Total de PDFs Processados:** 16 cadernos da OBI 2020 (`pj`, `p1`, `p2`, `senior` abrangendo fases 1, 1-b, 2 e 3).
- **Problemas Extraídos:** 57 problemas únicos após consolidação por nível (`pj`: 13, `p1`: 10, `p2`: 14, `senior`: 20).
- **Integração de Testes e Soluções:** `uv run python main.py --step organize-questions --ano 2020` integrou 1.682 casos de teste e 143 códigos de soluções oficiais.
- **Validação de Testes Unitários:** 111 testes aprovados com sucesso via `uv run pytest`.

