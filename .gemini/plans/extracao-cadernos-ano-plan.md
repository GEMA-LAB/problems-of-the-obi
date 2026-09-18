# PLANO DE IMPLEMENTACAO: Extracao de Cadernos por Ano OBI (1999-2024) - v0.1

- **Identificador:** `extracao-cadernos-ano-plan`
- **Especificação de Referência:** [`.gemini/specs/spec-extractor-llm.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-extractor-llm.md) e [`.gemini/specs/spec-extrator-estrutura-e-matcher.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/specs/spec-extrator-estrutura-e-matcher.md)
- **Branch de Trabalho:** `main` (ou branch dedicada de funcionalidade)
- **Skills Aplicadas:** [`.gemini/skills/plans/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/plans/SKILL.md), [`.gemini/skills/sdd/SKILL.md`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/.gemini/skills/sdd/SKILL.md)

---

## 1. Visão Geral e Objetivo

O objetivo deste plano é estabelecer a rotina de extração de problemas da OBI parametrizada **estritamente pelo ano**, cobrindo o período histórico de 1999 a 2024.
O processamento é iniciado pelo ano de **2024**, garantindo validação progressiva e ausência de erros estruturais antes de avançar para anos anteriores.

A rotina deve:
1. Receber como parâmetro principal apenas o ano (`--ano [ano]`).
2. Localizar automaticamente todos os cadernos PDF disponíveis em `cadernos/[ano]/` (percorrendo todos os níveis presentes: `pj`, `p1`, `p2`, `senior`).
3. Extrair fielmente cada questão respeitando o [`ProblemSchema`](file:///c:/Users/Victo/Desktop/Ufal/problems-of-the-obi/src/models/problem.py):
   - Enunciado completo com quebras de linha (`statement`).
   - Seções de entrada (`input`), saída (`output`) e restrições (`constraints`).
   - Casos de teste de exemplo completos (`examples`).
   - Metadados padronizados: `year`, `level` (minúsculo: `pj`, `p1`, `p2`, `senior`), `period` (`Fase 1`, `Fase 2`, `Fase 3`, `Fase Única`), `topics`, `rating` (`[100]`), `time_limit` e `memory_limit` calibrados para Python.
   - Ausência estrita do campo `difficulty`.
4. Salvar cada questão no caminho padronizado:
   `output_with_code/[ano]/[nivel]/[nome_questao]/problem.json`

---

## 2. Módulos e Arquivos Impactados

```text
problems-of-the-obi/
├── .gemini/
│   ├── plans/
│   │   └── extracao-cadernos-ano-plan.md            # Este plano de implementação
│   └── prompts/
│       ├── 032-extrair-questoes-cadernos-2024-api.md # Telemetria do Prompt 032
│       └── 033-extracao-por-ano-cadernos.md         # Telemetria do Prompt 033
├── cadernos/
│   └── 2024/                                        # 16 cadernos PDF (p1, p2, pj, senior)
├── output_with_code/
│   └── 2024/                                        # Destino padronizado de todos os problem.json de 2024
│       ├── pj/                                      # 14 questões (cf, f1, f2, f3)
│       ├── p1/                                      # 15 questões (auditoria e conformidade)
│       ├── p2/                                      # 18 questões (5 existentes + 13 novas)
│       └── senior/                                  # 17 questões (f1, f2-b, f2, f3)
└── main.py                                          # Orquestrador CLI com suporte a `--step extract-questions --ano [ano]`
```

---

## 3. Inventário Detalhado do Ano de 2024

| Nível | Caderno PDF | Fase / Período | Questões Contidas |
| :--- | :--- | :--- | :--- |
| **PJ** | `ProvaOBI2024_cfpj.pdf` | Fase Única | Altura da árvore, Vale-presente, Aventura na floresta mágica, Fábrica de tesouras |
| **PJ** | `ProvaOBI2024_f1pj.pdf` | Fase 1 | Ogro, Concurso, Bactérias |
| **PJ** | `ProvaOBI2024_f2pj.pdf` | Fase 2 | Avenida, Alfabeto alienígena, Atletismo |
| **PJ** | `ProvaOBI2024_f3pj.pdf` | Fase 3 | Cadeado, Amigos, Entrevistas de emprego, Hotel Nlogônia |
| **P1** | `ProvaOBI2024_cfp1.pdf` | Fase Única | Bibi e a árvore, Fefe e o jogos dos monstrinhos, Mistura de Poções, Fábrica de Tesouras |
| **P1** | `ProvaOBI2024_f1p1.pdf` | Fase 1 | Ogro, Relógio, Concurso |
| **P1** | `ProvaOBI2024_f2p1.pdf` | Fase 2 | Avenida, Alfabeto Alienígena, Dança de Formatura, Concatena Dígitos |
| **P1** | `ProvaOBI2024_f3p1.pdf` | Fase 3 | Musical, Entrevistas de emprego, Hotel Nlogônia, Brigadeiros |
| **P2** | `ProvaOBI2024_cfp2.pdf` | Fase Única | Bibi e a árvore, Mistura de Poções, Tabuleiro, Christina e os bombons, Estradas em Nlogônia |
| **P2** | `ProvaOBI2024_f1p2.pdf` | Fase 1 | Ogro, Relógio, Concurso, Jogo da Vida |
| **P2** | `ProvaOBI2024_f2p2.pdf` | Fase 2 | Cubo Preto, Alfabeto Alienígena, Concatena Dígitos, Jogo do Poder |
| **P2** | `ProvaOBI2024_f3p2.pdf` | Fase 3 | Brigadeiros, Construtora, Retas, Burocracia, Jogo de Pratos |
| **Senior** | `ProvaOBI2024_f1ps.pdf` | Fase 1 | Ogro, Concurso, Placas de Carro, Jogo da Vida |
| **Senior** | `ProvaOBI2024_f2p2-B.pdf` | Fase 2 | Game Show, Salada de Frutas, Trio de Palitinhos, Remove Dígitos |
| **Senior** | `ProvaOBI2024_f2ps.pdf` | Fase 2 | Cubo Preto, Alfabeto Alienígena, Dança de Formatura, Jogo do Poder |
| **Senior** | `ProvaOBI2024_f3ps.pdf` | Fase 3 | Brigadeiros, Construtora, Retas, Burocracia, Jogo de Pratos |

**Total de Questões de 2024:** 64 questões.

---

## 4. Checklist de Execucao

- [ ] **Fase 1:** Garantir telemetria e documentação dos prompts em `.gemini/prompts/`.
- [ ] **Fase 2:** Extração das 14 questões de `PJ` (CF, F1, F2, F3).
- [ ] **Fase 3:** Extração das 13 questões pendentes de `P2` (F1, F2, F3) e auditoria das 5 de CF.
- [ ] **Fase 4:** Extração das 17 questões de `Senior` (F1, F2-B, F2, F3).
- [ ] **Fase 5:** Auditoria e conformidade das 15 questões de `P1` já existentes.
- [ ] **Fase 6:** Validação sintática e de esquema via script automatizado e execução de `uv run pytest`.
