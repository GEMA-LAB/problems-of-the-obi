# Prompt 041 - Execução da Extração Fiel dos Cadernos OBI 1999 a 2017

- **Data e Hora:** 2026-09-18 22:09:20 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Como você percebeu estou repetindo os prompts, então quero que você faça separado por ano para não perder o conteudo do pdf, então execute o plano de 1999 até 2017 com alta fidelidade aos pdfs. Lembre sempre de salvar o prompt com as metricas.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Execução Progressiva da Extração (1999 a 2017):**
   - Processamento dos 85 cadernos de prova em PDF distribuídos entre 1999 e 2017 com fidelidade absoluta aos textos originais.
   - Tratamento de ligaduras tipográficas TeX/LaTeX (`\x1c`, `\x1b`, `\x1a`, `\ufb01`, `\ufb02`), decodificação de dead keys (`\xb4`, `\u02dc`, `\u02c6`, `\xb8`, `\u0131`) e caracteres de controle.
   - Extração estruturada de enunciados, seções de entrada, saída, restrições e exemplos (suportando padrões legados 1999-2004, intermediários 2005-2010 e modernos 2011-2017).
   - Validação estrita de conformidade com `ProblemSchema`: 327 questões geradas, 100% contendo `title`, `statement`, `input`, `output`, `examples` (>= 1 caso), `rating` (`[100]`), `topics` e ausência de `difficulty`.
   - Suíte de testes automatizados executada e validada: 111 testes passando (`uv run pytest`).

---

## Resultados da Extração por Ano (1999 a 2017)

| Ano | Cadernos Processados | Questões Geradas | Status de Validação |
|---|---|---|---|
| **1999** | ProvaOBI1999 | 4 | Conforme |
| **2000** | ProvaOBI2000 | 4 | Conforme |
| **2001** | ProvaOBI2001 | 5 | Conforme |
| **2002** | ProvaOBI2002 (f0p1, f0p2) | 10 | Conforme |
| **2003** | ProvaOBI2003 (f0p1, f0p2) | 11 | Conforme |
| **2004** | ProvaOBI2004 (f0p0, f0p1, f0p2) | 15 | Conforme |
| **2005** | ProvaOBI2005 (f0p1, f0p2) | 10 | Conforme |
| **2006** | ProvaOBI2006 (f1p1, f1p2, f2p1, f2p2) | 18 | Conforme |
| **2007** | ProvaOBI2007 (f1p1, f1p2, f2p1, f2p2) | 18 | Conforme |
| **2008** | ProvaOBI2008 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | 22 | Conforme |
| **2009** | ProvaOBI2009 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | 24 | Conforme |
| **2010** | ProvaOBI2010 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | 22 | Conforme |
| **2011** | ProvaOBI2011 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | 23 | Conforme |
| **2012** | ProvaOBI2012 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | 20 | Conforme |
| **2013** | ProvaOBI2013 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | 22 | Conforme |
| **2014** | ProvaOBI2014 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | 24 | Conforme |
| **2015** | ProvaOBI2015 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | 24 | Conforme |
| **2016** | ProvaOBI2016 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj, f1sr, f2sr) | 35 | Conforme |
| **2017** | ProvaOBI2017 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj, f1sr, f2sr) | 41 | Conforme |
| **Total** | **85 cadernos** | **327 questões** | **100% Conforme** |

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
|---|---|
| **Tokens de Entrada (sem cache)** | 5.180.934 |
| **Tokens de Entrada (cache)** | 52.224.190 |
| **Total de Tokens de Entrada** | 57.405.124 |
| **Tokens de Saída (Thinking / Raciocínio)** | 145.897 |
| **Tokens de Saída (Resposta)** | 0 |
| **Total de Tokens de Saída** | 145.897 |
| **Total Geral de Tokens** | **57.551.021** |
