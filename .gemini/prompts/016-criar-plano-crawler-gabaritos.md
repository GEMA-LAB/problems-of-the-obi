# Prompt 016 - Criar Plano para Crawler de Gabaritos e Casos de Teste

- **Data e Hora:** 2026-09-17 16:29:14 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
A partir da spec@[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\spec-crawler-gabaritos.md] crie um plano com @[.gemini/skills/plans/SKILL.md] para criar a funcionalidade
```

---

## Alinhamento e Diagnóstico Técnico

1. **Objetivo:**
   - Elaborar o plano técnico de implementação para o crawler de gabaritos e casos de teste (.zip) da OBI, baseado na especificação formal `.gemini/specs/spec-crawler-gabaritos.md` e seguindo as diretrizes de governança da skill `.gemini/skills/plans/SKILL.md`.

2. **Diretrizes Aplicadas:**
   - Criação da branch de trabalho `feat/crawler-gabaritos` a partir da branch principal `main`.
   - Divisão do trabalho em tarefas granulares com commits atômicos individuais (Conventional Commits, sem emojis).
   - Implementação orientada por testes (TDD) com cobertura de scraping, download idempotente, validação de integridade de ZIPs e sanitização de sistema de arquivos.
   - Integração completa ao CLI `main.py` sob a etapa `--step download-gabaritos`.
   - Abertura de Pull Request ao final do plano listando as alterações realizadas.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **1.420.043** |
| ↳ *Input sem cache* | 183.454 |
| ↳ *Input em cache (Prompt Cache)* | 1.236.589 |
| **Output Tokens (Total)** | **14.839** |
| ↳ *Thinking / Raciocínio* | 8.734 |
| ↳ *Respostas / Chamadas de Ferramenta* | 6.105 |
| **Total Geral (Input + Output)** | **1.434.882** |
| **Iterações / Chamadas ao Modelo** | **34** |

