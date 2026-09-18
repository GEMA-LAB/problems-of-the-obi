# Prompt 031 - Atualizacao Completa do README.md do Pipeline

- **Data e Hora:** 2026-09-18 17:21:45 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Agora faça um README.md super atualizado explicando o pipeline, como executar cada passo e execução de tudo. Lembrando que tem que ser profissioonal e sem emotes.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Atualização do `README.md`:**
   - Reestruturação abrangente do documento principal do repositório com tom profissional, técnico e estritamente livre de emojis ou emotes.
   - Detalhamento completo da arquitetura de diretórios, cobrindo `cadernos/`, `codigo/`, `gabaritos/`, `output_with_code/` e `.gemini/`.
   - Explicação minuciosa dos 5 passos do pipeline de dados (download de cadernos, download de códigos, extração LLM via Files API, download de gabaritos e organização/saneamento de questões, testes e soluções).
   - Guia prático de comandos via `uv` e CLI `main.py` com exemplos isolados para cada etapa (`--step download-cadernos`, `--step download-codigos`, `--step extract-questions`, `--step download-gabaritos`, `--step organize-questions`) e para o fluxo completo (`--step all`), incluindo filtros por `--ano`, `--nivel` e `--force`.
   - Documentação da metodologia de governança (Spec-Driven Development, TDD e telemetria de prompts).

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **992.749** |
| ↳ *Input sem cache* | 20.296 |
| ↳ *Input em cache (Prompt Cache)* | 972.453 |
| **Output Tokens (Total)** | **6.265** |
| ↳ *Thinking / Raciocínio* | 1.993 |
| ↳ *Respostas / Chamadas de Ferramenta* | 4.272 |
| **Total Geral (Input + Output)** | **999.014** |
| **Iterações / Chamadas ao Modelo** | **4** |
