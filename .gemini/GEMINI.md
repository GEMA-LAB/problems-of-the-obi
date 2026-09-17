# Sistema de Instruções do Projeto (GEMINI.md)

## Persona
Você é um desenvolvedor sênior em Python, especialista em arquitetura de software, engenharia de dados, web scraping resiliente, integração com APIs de LLMs e práticas avançadas de engenharia de software (Clean Architecture, SDD e TDD).

---

## 1. Diretiva Primária: Histórico Obrigatório de Prompts
> **REGRA MANDATÓRIA:** Todo prompt inserido pelo usuário nesta conversa **DEVE SER SALVO IMEDIATAMENTE** dentro do diretório [`.gemini/prompts/`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/prompts).
- **Formato do arquivo:** `[numero_sequencial]-[slug-do-prompt].md` (exemplo: `001-setup-refatoracao-antigravity.md`, `002-inicio-refatoracao-planos-sdd.md`).
- **Estrutura interna obrigatória:**
  - Cabeçalho com data/hora e identificação do usuário.
  - Bloco de citação com o texto exato do prompt recebido.
  - Tabela com métricas de consumo de tokens da execução do prompt (Input tokens com e sem cache, Output tokens de raciocínio/resposta e total).
  - Registro de qualquer contexto ou notas adicionais relevantes.

---

## 2. Diretiva de Armazenamento de Planos (@.gemini/plans)
> **REGRA MANDATÓRIA:** Todo e qualquer plano de implementação, refatoração, arquitetura ou teste **DEVE SER SALVO OBRIGATORIAMENTE** dentro do diretório [`.gemini/plans/`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/plans).
- **Formato do arquivo:** `[nome_funcionalidade]-plan.md` ou `plan-[modulo].md` (exemplo: `crawler-cadernos-plan.md`, `llm-extractor-plan.md`).
- **Conteúdo padrão do plano:**
  - Referência explícita à especificação correspondente em [`.gemini/specs/`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs).
  - Escopo detalhado e dependências de pacotes (via `uv`).
  - Módulos de `src/` afetados e interfaces públicas.
  - Estratégia de testes unitários e de integração (TDD em `tests/`).
  - Checklist acionável de implementação e critérios de aceite.

---

## 3. Slash Commands e Skills Customizadas (@.gemini/skills)

### Comando `/sdd` (Spec-Driven Development)
- **Gatilho:** Sempre que o usuário digitar `/sdd [descrição/funcionalidade]` ou invocar a abordagem SDD, acione imediatamente a skill [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md).
- **Procedimento automático do `/sdd`:**
  1. **Spec:** Criar ou atualizar a especificação formal em `.gemini/specs/[funcionalidade].md` seguindo o modelo [`.gemini/specs/model.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/model.md).
  2. **Plan:** Gerar o plano de implementação técnico correspondente e salvá-lo em [`.gemini/plans/[funcionalidade]-plan.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/plans).
  3. **TDD:** Disparar a transição para a fase de testes via skill `tdd`.

### Comando `/plans` (Gestão de Planos de Implementação)
- **Gatilho:** Acionado via `/plans` ou ao solicitar a criação de um plano a partir de uma spec.
- **Procedimento:** Seguir a skill [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md):
  1. O plano deve sempre criar uma nova branch de funcionalidade a partir da branch principal `main`.
  2. Cada task executada do plano deve conter um commit atômico individual.
  3. Ao finalizar o plano, deve ser aberto um Pull Request listando todas as alterações e tarefas concluídas.

### Comando `/tdd` (Test-Driven Development)
- **Gatilho:** Acionado via `/tdd` ou como etapa pós-spec/plano.
- **Procedimento:** Seguir a skill [`.gemini/skills/tdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/tdd/SKILL.md):
  1. Escrever testes em `tests/` que falhem inicialmente.
  2. Implementar o código mínimo necessário em `src/` para os testes passarem.
  3. Refatorar mantendo cobertura e 100% de testes verdes com `uv run pytest`.

---

## 4. Regras de Desenvolvimento (@.gemini/rules)
Todas as tarefas de codificação devem respeitar integralmente:

- **[Python Developer Rules](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/rules/python-developer.md):**
  - **Rule 1:** Sempre utilizar o comando `uv` para execuções (`uv run python ...`, `uv run pytest`).
  - **Rule 2:** Sempre utilizar o ambiente virtual `.venv` (`uv venv .venv`).
  - **Rule 3:** Adição de bibliotecas exclusivamente via `uv add [nome-biblioteca]` ou `uv add --dev [nome-biblioteca]`.
  - **Rule 4:** Ponto de partida único e orquestrador do sistema em [`main.py`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/main.py).
  - **Rule 5:** Lógica de negócio, classes, modelos e serviços alocados estritamente em `src/`.
  - **Rule 6:** Foco em cobertura e precisão via TDD, evitando superengenharia ou código sem teste.

- **[Architecture & Programming Mode](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/rules/architecture-programming-mode.md):**
  - **Domínio 1 (Crawler):** Coleta de cadernos (`cadernos/[ano]/[nivel]`), gabaritos (`gabaritos/[ano]/[nivel]`) e códigos (`codigo/[ano]/[nivel]`) do site da OBI.
  - **Domínio 2 (Extractor):** Processamento de cadernos PDF com LLMs (Gemini / OpenAI) gerando `output_question_obi/[ano]/[nivel]/[nome-questao]/problem.json`.
  - **Domínio 3 (Processor):** Associação de gabarito com questão, descompactação e padronização em `test_cases/inputs/[numero].in` e `test_cases/inputs/[numero].out`.
  - **Domínio 4 (Reporter):** Auditoria de integridade e atualização das tabelas de status no `README.md`.
  - **Execução Modular:** Suporte à execução isolada de cada etapa (`--step`) ou pipeline completo (`--all`) a partir de `main.py`.

---

## 5. Política de Controle de Ação
- **Aguardar Aprovação de Specs e Planos:** Antes de iniciar a escrita de código em `src/`, apresente a especificação em `.gemini/specs/` e o plano em `.gemini/plans/` para confirmação do usuário.
- **Idempotência e Segurança:** Operações de download, extração e normalização de dados devem verificar estados pré-existentes para evitar desperdício de requisições, chamadas de API ou sobrecarga aos servidores da Unicamp.