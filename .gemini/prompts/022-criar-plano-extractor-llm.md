# Prompt 022 - Criação do Plano para Extrator LLM via Skill Plans

- **Data e Hora:** 2026-09-17 18:08:11 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
A partir da spec @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\spec-extractor-llm.md] e crie um plano através do @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\skills\plans\SKILL.md]
```

---

## Alinhamento e Diagnóstico Técnico

1. **Objetivo do Plano:**
   - Estruturar o plano técnico detalhado para a implementação do domínio `extractor` ([`src/extractor/`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/extractor)), baseado estritamente na especificação [`.gemini/specs/spec-extractor-llm.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-extractor-llm.md).
   - O plano foi registrado em [`.gemini/plans/extractor-llm-plan.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/plans/extractor-llm-plan.md).

2. **Diretrizes da Skill `plans` (`.gemini/skills/plans/SKILL.md`):**
   - Criação de uma nova branch de funcionalidade a partir da branch principal (`feat/extractor-llm`).
   - Planejamento de tarefas atômicas com estratégia TDD, modelos de validação (`ProblemSchema`, `Exemplo`), sanitização de JSON, cliente OpenAI e orquestração.
   - Cada tarefa deve gerar um commit atômico individual.
   - Abertura de Pull Request ao término da execução do plano.

3. **Arquitetura e Escopo Técnico:**
   - Criação dos módulos em `src/extractor/`:
     - `src/models/problem.py`: Schemas e validação dos dados de saída (`ProblemSchema` com `time_limit` float e `memory_limit` int calibrados para Python e sem `difficulty`).
     - `src/prompts/extraction_prompt.md`: Template oficial do prompt com persona, task, regras e formato JSON estrito.
     - `src/extractor/prompt_loader.py`: Carregador do template de prompt.
     - `src/extractor/json_parser.py`: Sanitização de fences markdown e desserialização tolerante a falhas.
     - `src/extractor/openai_extractor.py`: Cliente OpenAI, Files API, requisição estruturada, garantia de exclusão no `finally` e gravação em `output/[titulo]/problem.json` (e `output/[titulo]_[ano]/`).
     - Integração no CLI (`main.py`) na etapa `--step extract-questions`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **5.024.077** |
| ↳ *Input sem cache* | 713.675 |
| ↳ *Input em cache (Prompt Cache)* | 4.310.402 |
| **Output Tokens (Total)** | **50.186** |
| ↳ *Thinking / Raciocínio* | 23.242 |
| ↳ *Respostas / Chamadas de Ferramenta* | 26.944 |
| **Total Geral (Input + Output)** | **5.074.263** |
| **Iterações / Chamadas ao Modelo** | **64** |
