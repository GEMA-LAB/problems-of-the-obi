# Prompt 028 - Criacao da Especificacao de Estrutura do Extrator e Matcher de Solucoes

- **Data e Hora:** 2026-09-18 16:39:58 -03:00
- **Usuário:** Victo

## Conteúdo do Prompt

```text
Através do @[c:\Users\Victo\Desktop\Ufal\problems-of-the-obi\.gemini\specs\model.md], crie uma spec para corrigir algumas coisas. Por exemplo, p extractor llm está criando diretorios como C:\Users\Victo\Desktop\Ufal\problems-of-the-obi\output_with_code\2025\n1, sendo que se você analisar o C:\Users\Victo\Desktop\Ufal\problems-of-the-obi\cadernos\2025 não possui nenhum diretório n1. Então, o extrator tem que seguir a estrutura do C:\Users\Victo\Desktop\Ufal\problems-of-the-obi\cadernos. Outro ponto, são os códigos de solução, não espere que o nome seja totalmente igual, por exemplo: existe esse diretorio C:\Users\Victo\Desktop\Ufal\problems-of-the-obi\codigo\2025\p1, então esses códigos desse diretorio podem está relacionado as questõs C:\Users\Victo\Desktop\Ufal\problems-of-the-obi\output_with_code\2025\p1.
```

---

## Alinhamento e Diagnóstico Técnico

1. **Diagnóstico do Extrator LLM:**
   - O `OpenAiExtractor` persistia questões baseando-se no campo `level` inferido pela LLM (ex: `N1`), gerando diretórios inconsistentes com a estrutura de entrada em `cadernos/` (ex: `output_with_code/2025/n1/`).
   - A árvore de pastas sob `output_with_code/` deve espelhar estritamente a hierarquia física de `cadernos/[ano]/[nivel]/`.

2. **Diagnóstico do Matcher de Soluções:**
   - O `ResourceMatcher` realizava comparações estritas ou incompletas, falhando ao associar arquivos de solução que contêm prefixos de autor, variações de técnica e identificadores parciais em `codigo/[ano]/[nivel]/` (ex: `recarga_carro.cpp`, `redes_1_freq_java.java`, `feira_artesanato_cpp.cpp`).

3. **Criação da Especificação:**
   - Elaborada a especificação `.gemini/specs/spec-extrator-estrutura-e-matcher.md` seguindo rigorosamente o template `.gemini/specs/model.md` com entidades, pré-condições, regras R1-R7, user stories E1-E4, invariantes I1-I3 e escopo negativo.

---

## Consumo de Tokens (Execução do Prompt)

| Métrica | Quantidade de Tokens |
| :--- | :--- |
| **Input Tokens (Total)** | **1.890.397** |
| ↳ *Input sem cache* | 218.400 |
| ↳ *Input em cache (Prompt Cache)* | 1.671.997 |
| **Output Tokens (Total)** | **31.051** |
| ↳ *Thinking / Raciocínio* | 21.499 |
| ↳ *Respostas / Chamadas de Ferramenta* | 9.552 |
| **Total Geral (Input + Output)** | **1.921.448** |
| **Iterações / Chamadas ao Modelo** | **41** |
