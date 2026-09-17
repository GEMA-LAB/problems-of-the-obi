# Prompt 012 - Criacao de Plano para o Crawler de Codigos via Skill Plans

- **Data e Hora:** 2026-09-17 14:29:18 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
crie um plano @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\skills\plans\SKILL.md] através da@[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\spec-crawler-codigos.md]
```

---

## Alinhamento e Diretrizes Aplicadas

1. **Skill Plans (`.gemini/skills/plans/SKILL.md`):**
   - Criacao de branch dedicada a partir de `main` (`feat/crawler-codigos`).
   - Cada tarefa deve conter um commit atomico correspondente.
   - Abertura de Pull Request ao final do plano listando as mudancas.

2. **Skill SDD (`.gemini/skills/sdd/SKILL.md`):**
   - Especificacao formal mapeada em `.gemini/specs/spec-crawler-codigos.md`.
   - Plano tecnico salvo em `.gemini/plans/crawler-codigos-plan.md`.
   - Checklist estruturado de execucao com criterios de aceite.

3. **Diretriz Profissional (`.gemini/GEMINI.md`):**
   - Padrao estritamente profissional sem emojis.
   - Orientacao por TDD e integracao modular via `main.py --step download-codigos`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **1.695.816** |
| ↳ *Input sem cache* | 428.662 |
| ↳ *Input em cache (Prompt Cache)* | 1.267.154 |
| **Output Tokens (Total)** | **17.852** |
| ↳ *Thinking / Raciocínio* | 9.532 |
| ↳ *Respostas / Chamadas de Ferramenta* | 8.320 |
| **Total Geral (Input + Output)** | **1.713.668** |
| **Iterações / Chamadas ao Modelo** | 34 |
