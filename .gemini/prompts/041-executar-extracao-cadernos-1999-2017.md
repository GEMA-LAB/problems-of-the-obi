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
   - Processamento de todos os cadernos de prova em PDF distribuídos em `cadernos/[1999..2017]/` com fidelidade estrita aos textos originais.
   - Tratamento de ligaduras tipográficas TeX/LaTeX (`\x1c`, `\x1b`, `\x1a`, `\ufb01`, `\ufb02`), decodificação de dead keys (`\xb4`, `\u02dc`, `\u02c6`, `\xb8`, `\u0131`) e caracteres de controle.
   - Extração estruturada de enunciados, seções de entrada, saída, restrições e exemplos (suportando padrões legados 1999-2004, intermediários 2005-2010 e modernos 2011-2017).
   - Validação estrita de conformidade com `ProblemSchema`: 309 questões únicas geradas no total, 100% contendo `title`, `statement`, `input`, `output`, `examples` (>= 1 caso de teste), `rating` (`[100]`), `topics` e ausência de `difficulty`.
   - Suíte de testes automatizados executada e validada: 111 testes passando (`uv run pytest`).

---

## Resultados da Extração por Ano (1999 a 2017)

| Ano | Cadernos no Repositório | Nível | Questões Geradas | Status de Validação |
|---|---|---|---|---|
| **1999** | ProvaOBI1999_f1p2, ProvaOBI1999_f2p2 | Programação Nível 2 | 9 | Conforme |
| **2000** | ProvaOBI2000_f1p2 | Programação Nível 2 | 5 | Conforme |
| **2001** | ProvaOBI2001_f1p2 | Programação Nível 2 | 5 | Conforme |
| **2002** | ProvaOBI2002_f1p2 | Programação Nível 2 | 5 | Conforme |
| **2003** | ProvaOBI2003_f0p0 | Programação Nível Sênior | 6 | Conforme |
| **2004** | ProvaOBI2004_f0p0 | Programação Nível Sênior | 5 | Conforme |
| **2005** | ProvaOBI2005 (f0p1, f0p2) | Programação Nível 1 e 2 | 9 | Conforme |
| **2006** | ProvaOBI2006 (f1p1, f1p2, f2p1, f2p2) | Programação Nível 1 e 2 | 14 | Conforme |
| **2007** | ProvaOBI2007 (f1p1, f1p2, f2p1, f2p2) | Programação Nível 1 e 2 | 13 | Conforme |
| **2008** | ProvaOBI2008 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | Nível Júnior, 1 e 2 | 21 | Conforme |
| **2009** | ProvaOBI2009 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | Nível Júnior, 1 e 2 | 21 | Conforme |
| **2010** | ProvaOBI2010 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | Nível Júnior, 1 e 2 | 23 | Conforme |
| **2011** | ProvaOBI2011 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | Nível Júnior, 1 e 2 | 20 | Conforme |
| **2012** | ProvaOBI2012 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | Nível Júnior, 1 e 2 | 20 | Conforme |
| **2013** | ProvaOBI2013 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | Nível Júnior, 1 e 2 | 11 | Conforme |
| **2014** | ProvaOBI2014 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | Nível Júnior, 1 e 2 | 24 | Conforme |
| **2015** | ProvaOBI2015 (f1p1, f1p2, f1pj, f2p1, f2p2, f2pj) | Nível Júnior, 1 e 2 | 23 | Conforme |
| **2016** | ProvaOBI2016 (f1p1..f2p2, f1pj, f2pj, f1pu, f2pu) | Júnior, 1, 2 e Sênior | 35 | Conforme |
| **2017** | ProvaOBI2017 (f1p1..f3p2, f1pj..f3pj, f1pu..f3pu) | Júnior, 1, 2 e Sênior | 40 | Conforme |
| **Total** | **78 cadernos disponíveis** | **Todos os níveis** | **309 questões** | **100% Conforme** |

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
|---|---|
| **Tokens de Entrada (sem cache)** | 5.792.105 |
| **Tokens de Entrada (cache)** | 56.302.808 |
| **Total de Tokens de Entrada** | 62.094.913 |
| **Tokens de Saída (Thinking / Raciocínio)** | 155.107 |
| **Tokens de Saída (Resposta)** | 0 |
| **Total de Tokens de Saída** | 155.107 |
| **Total Geral de Tokens** | **62.250.020** |
