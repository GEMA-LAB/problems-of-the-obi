# Prompt 018 - Criar Spec para Organizar Questões (Test Cases e Soluções)

- **Data e Hora:** 2026-09-17 17:21:55 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Crie uma spec através do @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\model.md] a parte do código:

# Passo 4: Cruzar ZIPs com Pastas Output
    if args.step in ["organize-testcases", "all"]:
        organizar_test_cases()
        if args.step == "organize-testcases":
            print("\nETAPA ORGANIZE-TESTCASES FINALIZADA COM SUCESSO.")
            return

Esses organizar_test_cases deve organizar tanto o test_cases e solution na questão respectiva. Pode ser um organizar question.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Objetivo:**
   - Criar uma especificação formal com base no modelo `.gemini/specs/model.md` para a funcionalidade de organização de questões, integrando tanto os casos de teste (`test_cases`) quanto os códigos de solução (`solution` / `solutions`) na estrutura de cada questão em `output_question_obi/`.

2. **Diretrizes e Regras do Projeto:**
   - Seguir rigorosamente o formato de `.gemini/specs/model.md`.
   - Proibição estrita de emojis em documentação, logs e código.
   - Observar as definições de arquitetura descritas em `.gemini/rules/architecture-programming-mode.md`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **1.648.915** |
| ↳ *Input sem cache* | 321.594 |
| ↳ *Input em cache (Prompt Cache)* | 1.327.321 |
| **Output Tokens (Total)** | **20.111** |
| ↳ *Thinking / Raciocínio* | 8.291 |
| ↳ *Respostas / Chamadas de Ferramenta* | 11.820 |
| **Total Geral (Input + Output)** | **1.669.026** |
| **Iterações / Chamadas ao Modelo** | **35** |

