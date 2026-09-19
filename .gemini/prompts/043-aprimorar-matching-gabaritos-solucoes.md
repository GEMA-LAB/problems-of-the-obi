# Prompt 043 - Aprimoramento do Matching de Gabaritos e Soluções no QuestionsOrganizer

- **Data e Hora:** 2026-09-18 23:00:19 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Ok, agora vamos verificar a execução uv run .\main.py --step organize-questions. Sei que não conseguiu pegar as soluções devido ter mais de 2 palavras e etc, assim como os gabaritos. Como a estrutra dos diretorios está parecido
```

---

## Alinhamento e Diagnóstico Técnico

1. **Contexto e Problema:**
   - O usuário identificou que na etapa `organize-questions`, muitas soluções e gabaritos não são associados às questões devido a títulos com múltiplas palavras, acentuações, abreviações nos arquivos fonte (ex: `cofrinhosdavovitoria` vs `cofre.c`, `supermercado` vs `super.c`, `torresdehanoi` vs `hanoi.c`) ou pequenas divergências entre o nome do arquivo compactado/código e o título do problema.
   - Como a estrutura de diretórios é hierárquica e similar (`[ano]/[nivel]/...` em `output_with_code`, `gabaritos` e `codigo`), podemos utilizar o contexto de ano, nível, fase e mapeamento semântico / trigramas / aliases para maximizar o pareamento.
2. **Investigação da Estrutura de Gabaritos e Código:**
   - Analisar como os arquivos em `gabaritos/` e `codigo/` estão nomeados e organizados para os anos de 1999 a 2024.
   - Analisar o algoritmo do `ResourceMatcher` em `src/processor/matcher.py`.
3. **Aprimoramento do `ResourceMatcher`:**
   - Melhorar o cálculo de correspondência para títulos compostos e stems de soluções/gabaritos.
   - Permitir match difuso baseado em tokens, containment mútuo, aliases canônicos e afinidade de diretório `[ano]/[nivel]`.
4. **Validação:**
   - Executar `organize-questions` e acompanhar as estatísticas de pareamento de gabaritos e soluções.
   - Rodar a suíte `uv run pytest`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade |
| :--- | :--- |
| **Tokens de Entrada (sem cache)** | 9.590.859 |
| **Tokens de Entrada (com cache)** | 92.754.615 |
| **Total de Entrada** | 102.345.474 |
| **Tokens de Saída (raciocínio/thinking)** | 218.072 |
| **Tokens de Saída (resposta)** | 0 |
| **Total Geral de Saída** | 218.072 |
| **Total Geral Consumido** | 102.563.546 |
| **Iterações de Execução** | 678 |

---

## Resultados da Implementação

1. **Aprimoramento do ResourceMatcher (`src/processor/matcher.py`):**
   - Implementado dicionário canônico `GLOBAL_ALIASES` cobrindo abreviações históricas da OBI (ex: `cofrinhosdavovitoria` -> `cofre`, `temperaturalunar` -> `lua`, `trespordois` -> `3por2`, `duplasdetenis` -> `tenis`, `donaformiga` -> `formiga`, `omarnaosataparapeixe` -> `pesca`, etc.).
   - Expandida a função `calculate_solution_match_score` para suportar:
     - Match por alias global (score 90).
     - Token líder do arquivo coincidente com qualquer token significativo da questão (score 70).
     - Prefixo do token líder do arquivo para stems truncados (score 60).
     - Desambiguação local contra questões irmãs na mesma fase e nível.
   - Refinado o método `find_gabarito` para incorporar consulta por aliases canônicos e correspondência difusa de substrings.
2. **Atualização da Idempotência em `QuestionsOrganizer` (`src/processor/questions_organizer.py`):**
   - Permitida a sincronização de soluções oficiais para pastas onde os testes já estavam previamente organizados (`force=False`), sem reprocessar testes existentes nem apagar dados.
3. **Métricas de Cobertura Após Execução:**
   - Total de questões analisadas: 753 (de 1999 a 2025).
   - Questões com testes unitários normalizados: 687 (100% das questões que possuem gabarito na OBI).
   - Questões com códigos de solução oficial associados: salto de 532 para 648 questões.
   - Total de arquivos de solução oficial organizados em disco: 444 novos vínculos concluídos.
4. **Validação de Testes:**
   - 100% dos 111 testes automatizados passando em `uv run pytest`.

