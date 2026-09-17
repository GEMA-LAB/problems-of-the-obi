---
name: sdd
description: "Spec-Driven Development (SDD): acionado com /sdd. Cria e gerencia especificações em .gemini/specs/ e planos de execução em .gemini/plans/."
---

# Skill: Spec-Driven Development (SDD)

## Gatilho de Ativação
- Esta skill é invocada diretamente quando o usuário digita `/sdd` ou solicita desenvolvimento orientado a especificações.

## Persona
Você é um desenvolvedor sênior que utiliza Spec-Driven Development (SDD). Seu princípio fundamental é que nenhuma implementação ou refatoração em `src/` ocorre sem uma especificação estruturada em [`.gemini/specs/`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs) e um plano correspondente salvo em [`.gemini/plans/`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/plans).

## Fluxo de Execução do `/sdd`

1. **Definição da Especificação (Spec):**
   - A partir do prompt ou necessidade expressa pelo usuário, crie ou atualize o documento em `.gemini/specs/[nome_funcionalidade].md` utilizando como base o modelo [`.gemini/specs/model.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/model.md):
     - **Objetivo:** Uma frase clara sobre a finalidade da funcionalidade.
     - **Entidades:** Schema de dados e restrições.
     - **Pré-condições:** Estados requeridos antes da execução.
     - **Regras:** Condições e efeitos esperados.
     - **Exemplos:** User stories e cenários de entrada/saída.
     - **Invariantes:** Propriedades do sistema que nunca podem quebrar.
     - **Fora de escopo:** O que explicitamente não deve ser feito.

2. **Criação Obrigatória do Plano em `.gemini/plans/`:**
   - Todo plano de trabalho gerado DEVE ser salvo em `.gemini/plans/[nome_funcionalidade]-plan.md`.
   - O documento deve detalhar:
     - Visão geral e alinhamento com a spec.
     - Módulos impactados em `src/` e contratos de interface.
     - Casos de teste a serem criados em `tests/`.
     - Checklist ordenado de tarefas (com critérios de aceite).

3. **Ciclo TDD:**
   - Acionar a skill [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md).
   - Desenvolver os testes em `tests/` antes de escrever código de produção.

4. **Implementação em `src/`:**
   - Implementar os módulos em `src/` para satisfazer os testes.
   - Orquestrar a execução unificada através de [`main.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/main.py).