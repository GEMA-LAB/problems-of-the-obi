# Dataset OBI — Nível Sênior (`dataset_obi_senior`)

Conjunto de problemas de programação da **Olimpíada Brasileira de Informática (OBI)** — modalidade **Programação Nível Sênior** (2016–2025), estruturado com enunciados padronizados, imagens sincronizadas, casos de teste oficiais normalizados e soluções oficiais em múltiplas linguagens.

---

## 1. Visão Geral de Completude

| Métrica | Valor | Status |
| :--- | :---: | :--- |
| **Total de questões** | **125** | 100% possuem `problem.json` válido |
| **Com `test_cases` E `solutions`** | **125 (100%)** | Nenhuma questão incompleta |
| **Apenas `test_cases` (sem `solutions`)** | **0** | — |
| **Apenas `solutions` (sem `test_cases`)** | **0** | — |
| **Sem `test_cases` e sem `solutions`** | **0** | — |
| **Total de casos de teste** | **4.681 pares** (9.362 arquivos `.in`/`.out`) | 100% pareados (`inputs/` $\leftrightarrow$ `outputs/` sem divergências) |
| **Questões com imagens (`imgs/`)** | **46 questões** (54 imagens `.png`) | 0 divergências entre pasta `imgs/`, campo `"imgs"` e tags `[N.png]` no `"statement"` |

---

## 2. Cobertura de Soluções por Linguagem (Total: 551 arquivos)

| Linguagem | Extensões | Questões cobertas (de 125) | Total de arquivos de solução |
| :--- | :---: | :---: | :---: |
| **C++** | `.cpp` | **123** (98,4%) | 228 |
| **Java** | `.java` | **93** (74,4%) | 107 |
| **Python** | `.py` | **92** (73,6%) | 125 |
| **JavaScript** | `.js` | **57** (45,6%) | 67 |
| **C** | `.c` | **20** (16,0%) | 24 |

---

## 3. Distribuição das 125 Questões por Ano

| Ano | Quantidade de Questões |
| :---: | :---: |
| **2016** | 10 |
| **2017** | 11 |
| **2019** | 12 |
| **2020** | 20 |
| **2021** | 16 |
| **2022** | 13 |
| **2023** | 13 |
| **2024** | 17 |
| **2025** | 13 |
| **Total** | **125** |

---

## 4. Estrutura de Diretórios de Cada Questão

Cada subdiretório representa uma questão e segue a estrutura abaixo:

```text
dataset_obi_senior/
└── <Nome da Questão>/
    ├── problem.json          # Metadados, enunciado, restrições e exemplos
    ├── imgs/                 # (Opcional) Figuras do enunciado (1.png, 2.png, ...)
    ├── solutions/            # Soluções oficiais (.cpp, .py, .java, .js, .c)
    └── test_cases/           # Casos de teste oficiais normalizados
        ├── inputs/           # Arquivos de entrada (1.in, 2.in, ...)
        └── outputs/          # Arquivos de saída esperada (1.out, 2.out, ...)
```

### Esquema do `problem.json`

```json
{
    "title": "Título da Questão",
    "statement": "Enunciado completo (com marcadores [1.png] posicionados onde há figuras)...",
    "input": "Descrição do formato de entrada...",
    "output": "Descrição do formato de saída...",
    "constraints": "Restrições e subtarefas...",
    "examples": [
        {
            "input": "...",
            "output": "..."
        }
    ],
    "imgs": ["1.png"],
    "rating": [100],
    "year": "2024",
    "level": "senior",
    "period": "Fase 1",
    "topics": ["..."],
    "time_limit": 1.0,
    "memory_limit": 512
}
```
