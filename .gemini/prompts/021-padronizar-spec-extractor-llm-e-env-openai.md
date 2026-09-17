# Prompt 021 - Padronização da Spec Extractor-LLM e Configuração .env OpenAI

- **Data e Hora:** 2026-09-17 17:47:46 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Essa spec @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\spec-extractor-llm.md] não está padronizado e precisa ser deixado com a estrutura atual que está no @[main.py]. Além disso, o `.env` deve ter ser focado a biblioteca OpenAI para utilizar apenas url base, a key e o modelo que os mesmos utilizam. Não ter difficulty, adicionar o time limit e memory limit focado na interpretação da questão para resolver ela com a linguagem python
```

---

## Alinhamento e Diagnóstico Técnico

1. **Padronização da Especificação (`.gemini/specs/spec-extractor-llm.md`):**
   - Adequação completa ao formato padrão estabelecido em `.gemini/specs/model.md` e alinhamento com a estrutura de diretórios em `main.py` (`output/[titulo]/problem.json` e `output/[titulo]_[ano]/`).
   - Ajuste das entidades do schema:
     - **Remoção** total do atributo `difficulty`.
     - **Inclusão** dos atributos `time_limit: float!` (em segundos) e `memory_limit: int!` (em MB), calibrados a partir do enunciado e restrições para viabilizar e orientar a resolução do problema em linguagem Python.
   - Formalização de regras voltadas ao cliente oficial da OpenAI (`openai.OpenAI`), Files API nativa e exclusão mandatória no bloco `finally`.

2. **Foco do `.env` na Biblioteca OpenAI:**
   - Criação e padronização dos arquivos `.env` e `.env.example` restritos às configurações necessárias para o cliente da OpenAI:
     - `OPENAI_BASE_URL` (URL base da API para provedor oficial ou endpoints compatíveis)
     - `OPENAI_API_KEY` (Chave de autenticação da API)
     - `OPENAI_MODEL` (Nome do modelo LLM a ser invocado)

3. **Alinhamento em `main.py`:**
   - Atualização da função `create_questions_gpt` em `main.py` para instanciar `OpenAI` lendo `OPENAI_BASE_URL`, `OPENAI_API_KEY` e `OPENAI_MODEL`.
   - Atualização do prompt de extração em `main.py`, instruindo a interpretação de `time_limit` e `memory_limit` com foco na linguagem Python e eliminando o campo de dificuldade.
   - Ativação do extrator OpenAI como fluxo padrão na etapa `extract-questions`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **3.567.827** |
| ↳ *Input sem cache* | 531.873 |
| ↳ *Input em cache (Prompt Cache)* | 3.035.954 |
| **Output Tokens (Total)** | **36.906** |
| ↳ *Thinking / Raciocínio* | 12.712 |
| ↳ *Respostas / Chamadas de Ferramenta* | 24.194 |
| **Total Geral (Input + Output)** | **3.604.733** |
| **Iterações / Chamadas ao Modelo** | **50** |
