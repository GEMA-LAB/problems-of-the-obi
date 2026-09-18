# Prompt 025 - Criação do Plano para Organização de Questões, Casos de Teste e Soluções

- **Data e Hora:** 2026-09-17 21:36:28 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

\\	ext
A partir da spec @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\spec-organize-questions.md] faça um plano através do @[.gemini/skills/plans/SKILL.md]
\
---

## Alinhamento e Diagnóstico Técnico

1. **Objetivo do Plano:**
   - Estruturar o plano técnico detalhado para a implementação do domínio processor (\src/processor/\), responsável pela correspondência, extração e organização padronizada tanto dos casos de teste (pares de entrada/saída) quanto dos códigos de soluções oficiais na estrutura de diretórios das questões (\output_with_code/\ / \output_question_obi/\), além do expurgo rigoroso de resíduos e de questões sem testes válidos.
   - O plano técnico foi registrado no artefato \implementation_plan.md\ e versionado em [\.gemini/plans/organize-questions-plan.md\](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/plans/organize-questions-plan.md).

2. **Diretrizes da Skill \plans\ (\.gemini/skills/plans/SKILL.md\):**
   - Criação de uma nova branch de funcionalidade a partir da branch principal (\eat/organize-questions\ a partir de \main\).
   - Planejamento de tarefas atômicas com abordagem TDD cobrindo:
     - Modelos de dados em \src/models/test_case.py\ (\QuestionFolder\, \TestCasePair\, \TestCaseSource\, \SolutionSource\, \OrganizeConfig\, \OrganizeResult\).
     - Módulo de correspondência e normalização Unicode NFD estrita (\src/processor/matcher.py\).
     - Módulo de descompactação segura de arquivos ZIP com tolerância a falhas (\src/processor/zip_extractor.py\).
     - Módulo de normalização sequencial de pares \.in\ e \.out\ em \	est_cases/inputs/\ e \	est_cases/outputs/\ (\src/processor/normalizer.py\).
     - Módulo de limpeza e expurgo seguro de executáveis, lixo residual e questões órfãs (\src/processor/cleaner.py\).
     - Orquestrador central do domínio (\src/processor/questions_organizer.py\).
     - Integração no CLI (\main.py\) na etapa \--step organize-questions\ (com alias \--step organize-testcases\, \--ano\, \--nivel\, \--force\).
   - Cada tarefa gerará um commit atômico individual.
   - Abertura de Pull Request ao término da execução do plano.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **2.293.933** |
| ↳ *Input sem cache* | 351.603 |
| ↳ *Input em cache (Prompt Cache)* | 1.942.330 |
| **Output Tokens (Total)** | **25.849** |
| ↳ *Thinking / Raciocínio* | 14.803 |
| ↳ *Respostas / Chamadas de Ferramenta* | 11.046 |
| **Total Geral (Input + Output)** | **2.319.782** |
| **Iterações / Chamadas ao Modelo** | **42** |
