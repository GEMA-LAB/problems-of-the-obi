# Prompt 039 - Execução da Extração Fiel dos Cadernos OBI 2019

- **Data e Hora:** 2026-09-18 20:52:27 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Agora é apenas repetição do plano para o ano de 2019 com alta fidelidade aos pdfs. Lembre sempre de salvar o prompt com as metricas.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Execução da Extração para o Ano de 2019:**
   - Mapeamento e inspeção de todos os cadernos PDF em `cadernos/2019/`.
   - Extração fiel dos enunciados, restrições, entradas, saídas e exemplos de teste.
   - Normalização e validação dos dados segundo o `ProblemSchema`.
   - Gravação dos arquivos `problem.json` em `output_with_code/2019/[nivel]/[nome da questão]/`.
   - Execução do organizador de testes/soluções e validação com `uv run pytest`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade |
| :--- | :--- |
| **Tokens de Entrada (sem cache)** | 356.455 |
| **Tokens de Entrada (cache)** | 2.631.872 |
| **Total de Tokens de Entrada** | 2.988.327 |
| **Tokens de Saída (Thinking)** | 7.512 |
| **Tokens de Saída (Resposta)** | 0 |
| **Total de Tokens de Saída** | 7.512 |
| **Total Geral de Tokens** | 2.995.839 |
| **Total de Iterações / Chamadas** | 21 |

---

## Resultados da Execução

- **Total de PDFs Processados:** 10 cadernos da OBI 2019 (`pj`, `p1`, `p2`, `senior` abrangendo Fases 1, 2 e 3).
- **Problemas Extraídos:** 37 problemas únicos (`pj`: 9, `p1`: 11, `p2`: 12, `senior`: 5).
- **Integração de Testes e Soluções:** `uv run python main.py --step organize-questions --ano 2019` integrou 1.726 casos de teste e 117 códigos de soluções oficiais.
- **Validação de Testes Unitários:** 111 testes aprovados com sucesso via `uv run pytest`.

