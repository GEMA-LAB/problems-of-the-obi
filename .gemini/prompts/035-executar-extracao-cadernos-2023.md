# Prompt 035 - Execução da Extração Fiel dos Cadernos OBI 2023

- **Data e Hora:** 2026-09-18 20:23:35 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Agora é apenas repetição do plano para o ano de 2023 com alta fidelidade aos pdfs. Lembre sempre de salvar o prompt com as metricas.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Extração e Construção do Ano de 2023:**
   - Levantamento e inspeção completa dos 15 cadernos PDF em `cadernos/2023/`.
   - Extração fiel dos 57 problemas distribuídos nos 4 níveis de competição:
     - `pj` (14 problemas): *Conversa dos Pinguins*, *Estante de Livros*, *Suco Radioativo*, *A Grande Casquinha*, *Prêmio*, *Epidemia*, *Chinelos*, *Pizza da OBI*, *Código de Compressão*, *Grupos de Trabalho*, *Cabo de Guerra*, *Tesouro*, *Metrônibus*, *Oficina Mecânica*.
     - `p1` (14 problemas): *Estante de Livros*, *Suco Radioativo*, *Machine Learning*, *Garrafões*, *VAR*, *Estoque*, *Subsequência*, *Prefixo*, *Grupos de Trabalho*, *Intervalo Distinto*, *Cabo de Guerra*, *Metrônibus*, *Dominó Nlogônico*, *Oficina Mecânica*.
     - `p2` (16 problemas): *Estante de Livros*, *Machine Learning*, *Viagem*, *Contas a Pagar*, *Leilão*, *Estoque*, *Toupeira*, *Código de Compressão*, *Grupos de Trabalho*, *Intervalo Distinto*, *Barcos da Nlogônia*, *Pirâmide*, *Transportes*, *Oficina Mecânica*, *Trio de Bonecas*, *Fast-Food*.
     - `senior` (13 problemas): *Contas a Pagar*, *Estoque*, *Subsequência*, *Sr. Toupeira*, *Prefixo*, *Grupos de Trabalho*, *Intervalo Distinto*, *Barcos da Nlogônia*, *Pirâmide*, *Transportes*, *Oficina Mecânica*, *Trio de Bonecas*, *Fast-Food*.
2. **Validação de Conformidade Estrutural:**
   - 100% dos 57 problemas validados via `ProblemSchema.from_dict` com sucesso.
   - Enunciados completos mantendo formatação original e quebras de linha (`statement`), seções de entrada (`input`), saída (`output`), restrições (`constraints`) e exemplos (`examples`).
   - Limites de tempo e memória calibrados para Python e sem o campo `difficulty`.
3. **Organização e Casos de Teste:**
   - Execução de `main.py --step organize-questions --ano 2023` com 57 questões identificadas, 2.896 casos de teste vinculados e 434 arquivos de soluções oficiais associados.
   - Suíte de 111 testes unitários com 100% de aprovação via `uv run pytest`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **6.706.794** |
| ↳ *Input sem cache* | 796.016 |
| ↳ *Input em cache (Prompt Cache)* | 5.910.778 |
| **Output Tokens (Total)** | **16.460** |
| ↳ *Thinking / Raciocínio* | 16.460 |
| ↳ *Respostas / Chamadas de Ferramenta* | 0 |
| **Total Geral (Input + Output)** | **6.723.254** |
| **Iterações / Chamadas ao Modelo** | **29** |
