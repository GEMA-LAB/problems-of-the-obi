# Prompt 024 - Ajuste do Padrão de Diretório para output_with_code/[ano]/[nivel]/[nome_questao]/

- **Data e Hora:** 2026-09-17 18:52:22 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Coloquei para criar aqui@[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\output_with_code] , porém não está fazendo no padrão output_with_code/[ano]/[nivel]/[nome_questão]/problem.json. Faça as alterações e consequentemente modifique o @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\spec-extractor-llm.md]
```

---

## Alinhamento e Diagnóstico Técnico

1. **Atualização da Especificação (`.gemini/specs/spec-extractor-llm.md`):**
   - Atualizada a especificação para a versão `v0.3`.
   - Objetivo, `ExtractorConfig`, regras R6/R7, exemplos e invariante I3 modificados para definir estritamente a saída em `output_with_code/[ano]/[nivel]/[nome_questao]/problem.json`.

2. **Ajustes de Implementação:**
   - `src/core/config.py`: Constante `DEFAULT_OUTPUT_DIR` padronizada como `Path("output_with_code")`.
   - `src/extractor/openai_extractor.py`:
     - Método `save_problem` atualizado para gravar no caminho `base_dir / ano / nivel / clean_title / "problem.json"`, com `nivel` em caixa baixa (`pj`, `p1`, `p2`, `senior`, `geral`).
     - Inicialização de `OpenAiExtractor` protegida contra exceção prematura na ausência de credenciais em testes/scripts utilitários.
   - `main.py`: Funções `create_questions`, `create_questions_gpt` e orquestrador atualizados para o padrão `output_with_code/{ano}/{nivel}/{titulo}/problem.json`.
   - `tests/unit/test_openai_extractor.py`: Testes unitários atualizados e validados com a nova estrutura de pastas.

3. **Validação de Testes e Controle de Versão:**
   - 74 testes unitários executados com 100% de sucesso.
   - Commit atômico gerado na branch `feat/extractor-llm` e enviado para o Pull Request #4.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **29.327.040** |
| ↳ *Input sem cache* | 2.829.433 |
| ↳ *Input em cache (Prompt Cache)* | 26.497.607 |
| **Output Tokens (Total)** | **113.185** |
| ↳ *Thinking / Raciocínio* | 64.650 |
| ↳ *Respostas / Chamadas de Ferramenta* | 48.535 |
| **Total Geral (Input + Output)** | **29.440.225** |
| **Iterações / Chamadas ao Modelo** | **196** |
