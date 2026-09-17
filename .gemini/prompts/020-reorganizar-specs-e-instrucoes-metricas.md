# Prompt 020 - Reorganização de Specs (Organize Questions e Processor) e Diretiva de Métricas

- **Data e Hora:** 2026-09-17 17:38:33 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
@[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\spec-processor-testcases.md] @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\spec-organize-questions.md] parece as specs tem coisas em comum, reorganize para ficar apenas uma spec e os prompts não está colocando as metricas como@[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\prompts\018-criar-spec-organizar-questoes.md]. Sempre coloque a metrica e deixe plano no @[.gemini/GEMINI.md]
```

---

## Alinhamento e Diagnóstico Técnico

1. **Consolidação de Especificações:**
   - Analisar comparativamente `spec-processor-testcases.md` e `spec-organize-questions.md`.
   - Fundir as duas especificações em uma única especificação coesa e abrangente (`spec-organize-questions.md` ou formato unificado de processador/organizador de questões), cobrindo a associação da questão tanto com seus casos de teste compactados/extraídos (`test_cases`) quanto com suas soluções oficiais (`solutions` / `solution`).
   - Remover a especificação redundante após consolidação para evitar duplicação ou divergência de regras.

2. **Preenchimento de Métricas de Tokens do Prompt 018:**
   - Extrair a telemetria do Prompt 018 e preencher sua tabela de consumo de tokens em `.gemini/prompts/018-criar-spec-organizar-questoes.md`.

3. **Atualização do `GEMINI.md` (Diretiva Mandatória de Métricas):**
   - Reforçar explicitamente na Seção 1 de `.gemini/GEMINI.md` a obrigatoriedade de preenchimento contínuo das tabelas de métricas de tokens com as instruções técnicas de extração via `gen_metadata` no banco SQLite da sessão (`conversations/<id>.db`).

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **8.161.311** |
| ↳ *Input sem cache* | 1.180.588 |
| ↳ *Input em cache (Prompt Cache)* | 6.980.723 |
| **Output Tokens (Total)** | **22.456** |
| ↳ *Thinking / Raciocínio* | 15.236 |
| ↳ *Respostas / Chamadas de Ferramenta* | 7.220 |
| **Total Geral (Input + Output)** | **8.183.767** |
| **Iterações / Chamadas ao Modelo** | **41** |

