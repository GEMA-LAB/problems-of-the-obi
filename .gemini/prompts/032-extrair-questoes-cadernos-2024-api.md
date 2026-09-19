# Prompt 032 - Planejamento para Extracao Fiel dos Cadernos OBI 2024

- **Data e Hora:** 2026-09-18 19:55:54 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Veja esse código:

for pdf_path in cadernos_paths:
            try:
                problems = self.extract_from_pdf(pdf_path)
                if not problems:
                    errors.append(pdf_path)
                    continue

                for p in problems:
                    self.save_problem(p, output_base=output_base, source_pdf=pdf_path)
                    extracted_all.append(p)

            except Exception as e:
                logger.error(f"Erro ao processar caderno {pdf_path}")
                errors.append(pdf_path)

Note que ele está utilizando uma chamada da API na llm para conseguir construir o C:\Users\Victo\Desktop\Ufal\problems-of-the-obi\output_with_code\[ano]\[nivel]\[nome da questão]\problem.json. Então, queria que você faça isso sendo fiel ao conteudo dos pdfs C:\Users\Victo\Desktop\Ufal\problems-of-the-obi\cadernos\2024; A ideia é você fazer o que o código faz só que utilizando sua api e construindo primeiramente o ano de 2024.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Análise do Fluxo do Extrator:**
   - O snippet fornecido reflete o método `process_cadernos` de `OpenAiExtractor` em `src/extractor/openai_extractor.py`.
   - O objetivo do usuário é gerar a catalogação de todos os problemas do ano de 2024 no formato `output_with_code/[ano]/[nivel]/[nome da questão]/problem.json` com total fidelidade aos PDFs originais de `cadernos/2024/`.
   - Levantamento dos 16 cadernos PDF de 2024 em `p1`, `p2`, `pj` e `senior`, totalizando 64 problemas (20 pré-existentes para auditoria e 44 pendentes de extração).
2. **Criação do Plano de Implementação:**
   - Elaboração do plano formal de extração e validação conforme `ProblemSchema` com `time_limit` e `memory_limit` calibrados para Python e sem o campo `difficulty`.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **5.896.796** |
| ↳ *Input sem cache* | 843.833 |
| ↳ *Input em cache (Prompt Cache)* | 5.052.963 |
| **Output Tokens (Total)** | **42.255** |
| ↳ *Thinking / Raciocínio* | 14.121 |
| ↳ *Respostas / Chamadas de Ferramenta* | 28.134 |
| **Total Geral (Input + Output)** | **5.939.051** |
| **Iterações / Chamadas ao Modelo** | **74** |
