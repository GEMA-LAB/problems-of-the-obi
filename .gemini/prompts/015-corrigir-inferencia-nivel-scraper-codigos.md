# Prompt 015 - Correção na Inferência de Nível do Scraper de Códigos

- **Data e Hora:** 2026-09-17 15:10:02 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
A implementação está realmente baixando os códigos das páginas, porém está sempre como 'senior' e isso não é bem verdade. Na linha do código scraper.py existe uma função chamada de extract_code_links e é dedfino que nivel nivel = self.infer_level_or_phase(f"{page_url} {href}", link_text, filename) e nesse momento não esta reconhecendo os p1, p2, pj e etc. Conserte isso.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Causa Raiz Identificada:**
   - No método `infer_level_or_phase`, a checagem de nível sênior incluía a substring `"ps"` de forma ingênua (`"ps" in combined_text`).
   - Como o parâmetro `url_path` passado incluía `f"{page_url} {href}"`, qualquer URL com o protocolo `https://` contém a substring `"ps"` (de `https`), disparando o retorno de `"senior"`.
   - Além disso, para soluções oficiais, a estrutura do caminho no portal da OBI segue o padrão `/solucoes/{ano}f{fase}{nivel}_{problema}/{arquivo}` (ex: `2022f1p1_show`, `2022f1p2_bombom`, `2022f1pj_cinema`, `2022f1ps_trofeu`), onde `p1` e `p2` aparecem antecedidos pela fase (`f1p1_`, `f1p2_`) e não com `_p1` ou `nível 1`, falhando as checagens anteriores de `p1` e `p2`.

2. **Ações Corretivas:**
   - Implementar testes unitários específicos em `tests/unit/test_scraper_codigos.py` reproduzindo o falso positivo para `senior` e validando o reconhecimento de `p1`, `p2`, `pj` e `senior`.
   - Refinar `infer_level_or_phase` para:
     1. Desconsiderar o prefixo de protocolo `https://` / `http://` nas checagens de substring.
     2. Reconhecer padrões específicos de soluções da OBI como `f\d+pj`, `f\d+p1`, `f\d+p2`, `f\d+ps`, `f\d+pu`, `f\d+senior` e com delimitadores `_` ou limites de palavra (`_p1_`, `_p2_`, `_pj_`, `_ps_`, `p1_`, `p2_`, `pj_`, `ps_`).
     3. Substituir a busca ingênua por `"ps"` por padrões delimitados (ex: `_ps`, `ps_`, `f\d+ps`).
   - Reexecutar testes unitários e validação com o pipeline real.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **6.561.855** |
| ↳ *Input sem cache* | 487.197 |
| ↳ *Input em cache (Prompt Cache)* | 6.074.658 |
| **Output Tokens (Total)** | **19.010** |
| ↳ *Thinking / Raciocínio* | 11.920 |
| ↳ *Respostas / Chamadas de Ferramenta* | 7.090 |
| **Total Geral (Input + Output)** | **6.580.865** |
| **Iterações / Chamadas ao Modelo** | 34 |
