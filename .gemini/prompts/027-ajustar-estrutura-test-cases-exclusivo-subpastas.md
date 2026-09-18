# Prompt 027 - Ajuste da Estrutura de Test Cases para Subpastas Exclusivas (inputs/ e outputs/)

- **Data e Hora:** 2026-09-18 15:22:05 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
está quase tudo correto, entretando se você verificar os @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\output_with_code\2025\n1\Café com Leite\test_cases] está com as entradas e saída ainda. Conserte isso
```

---

## Alinhamento e Diagnóstico Técnico

1. **Diagnóstico do Problema:**
   - O diretório `test_cases/` estava armazenando os casos de teste em duplicidade: simultaneamente nas subpastas `test_cases/inputs/[numero].in` e `test_cases/outputs/[numero].out` e soltos diretamente na raiz de `test_cases/` (`1.in`, `1.out`, etc.).
   - Conforme alinhado com o usuário e documentado na arquitetura do repositório (`README.md`), a estrutura canônica exige armazenamento exclusivo sob `test_cases/inputs/` e `test_cases/outputs/`, sem arquivos residuais soltos na raiz de `test_cases/`.

2. **Ajustes Realizados:**
   - `src/processor/normalizer.py`: Removida a cópia redundante de arquivos para a raiz de `test_cases/`, mantendo a escrita unicamente em `inputs/` e `outputs/`.
   - `src/processor/cleaner.py`: Atualizado o método `clean_test_cases_residuals` para expurgar rigorosamente qualquer arquivo solto que resida na raiz de `test_cases/`, preservando apenas as subpastas `inputs/` e `outputs/`.
   - `src/processor/questions_organizer.py`: Adicionada limpeza preventiva de arquivos soltos na raiz de `test_cases/` mesmo durante checagens de idempotência (`force=False`).
   - `.gemini/specs/spec-organize-questions.md`: Atualizada a Regra R4 para explicitar a exigência de armazenamento exclusivo sob `test_cases/inputs/` e `test_cases/outputs/`.
   - Limpeza em lote executada em todas as questões existentes em `output_with_code/`, removendo 1.220 arquivos duplicados da raiz de `test_cases/`.
   - `tests/unit/`: Atualizados os testes unitários de `test_normalizer.py`, `test_cleaner.py` e `test_questions_organizer.py` com asserções estritas que garantem a ausência de arquivos na raiz de `test_cases/`.

3. **Validação de Testes:**
   - Suíte de 105 testes unitários executada com 100% de sucesso via `uv run pytest`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **9.899.638** |
| ↳ *Input sem cache* | 1.360.745 |
| ↳ *Input em cache (Prompt Cache)* | 8.538.893 |
| **Output Tokens (Total)** | **42.389** |
| ↳ *Thinking / Raciocínio* | 13.454 |
| ↳ *Respostas / Chamadas de Ferramenta* | 28.935 |
| **Total Geral (Input + Output)** | **9.942.027** |
| **Iterações / Chamadas ao Modelo** | **99** |
