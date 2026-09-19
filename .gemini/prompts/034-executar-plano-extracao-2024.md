# Prompt 034 - Execução do Plano de Extração dos Cadernos 2024

- **Data e Hora:** 2026-09-18 20:11:07 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Execute o plano
```

---

## Alinhamento e Diagnóstico Técnico

1. **Execução do Plano de Extração (`.gemini/plans/extracao-cadernos-ano-plan.md`):**
   - Extração fiel de todas as questões dos 16 cadernos PDF de 2024 (`cadernos/2024/`).
   - Cobertura completa dos 4 níveis:
     - `pj`: 14 questões geradas e validadas (`cfpj`, `f1pj`, `f2pj`, `f3pj`).
     - `p1`: 15 questões auditadas e consolidadas (`cfp1`, `f1p1`, `f2p1`, `f3p1`), com saneamento de duplicidade de pasta (`Danca de Formatura` -> `Dança de Formatura`).
     - `p2`: 18 questões geradas e validadas (`cfp2`, `f1p2`, `f2p2`, `f3p2`).
     - `senior`: 17 questões geradas e validadas (`f1ps`, `f2p2-B`, `f2ps`, `f3ps`).
   - Total: 64 problemas em `output_with_code/2024/[nivel]/[nome da questão]/problem.json`.
2. **Validação de Esquema e Integridade:**
   - 100% dos problemas validados com `ProblemSchema.from_dict` sem exceções.
   - Presença obrigatória de `statement`, `input`, `output`, `constraints` e `examples`.
   - Limites de tempo (`time_limit`) e memória (`memory_limit`) calibrados para resolução em Python.
   - Ausência estrita do campo `difficulty` em todos os arquivos JSON.
3. **Integração com Organizador e Testes:**
   - Execução de `main.py --step organize-questions --ano 2024` com 64 questões descobertas, 2.922 casos de teste e 662 códigos oficiais associados.
   - Suíte de 111 testes unitários com 100% de aprovação via `uv run pytest`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **8.216.196** |
| ↳ *Input sem cache* | 608.406 |
| ↳ *Input em cache (Prompt Cache)* | 7.607.790 |
| **Output Tokens (Total)** | **32.141** |
| ↳ *Thinking / Raciocínio* | 20.825 |
| ↳ *Respostas / Chamadas de Ferramenta* | 11.316 |
| **Total Geral (Input + Output)** | **8.248.337** |
| **Iterações / Chamadas ao Modelo** | **45** |
