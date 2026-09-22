# Plano de Implementacao: Sincronizacao de Imagens e Statements no Dataset OBI Python

## 1. Contexto e Objetivo

O usuario solicitou a verificacao dos 180 problemas listados entre os diretorios `output/` e `dataset_obi_python/`, tratando os problemas que possuem imagens (`imgs/`) e casos de teste (`test_cases/`):
1. **Status atual:** Os primeiros 60 nomes da lista ja foram checados pelo usuario (21 questoes ja possuem imagens sincronizadas).
2. **Meta:** Processar os 120 nomes restantes (de `Dividindo o império` ate `Ônibus`), alem de corrigir discrepancias de nomenclatura por ano (`nome_ano` como `Chuva_2019`, `Dominó_2019`, `Móbile_2015`, `Palavras Cruzadas_2020`, `Quadrado Mágico_2022`, `Robô_2021`, `Fila_2025`).
3. **Acoes para questoes coincidentes:**
   - Copiar a pasta `imgs/` de `output/[origem]/imgs` para `dataset_obi_python/[destino]/imgs`.
   - Atualizar `problem.json` no dataset:
     - Campo `"imgs"`: lista de arquivos de imagem (`["1.png"]`, `["1.png", "2.png"]`, etc.).
     - Campo `"statement"`: incorporar o texto de `output` contendo as tags `[1.png]`, preservando qualquer cabecalho de arquivos fonte (`Nome do arquivo:...`) presente originalmente no dataset.
4. **Questoes sem correspondencia no dataset:** Nao sofrem alteracoes no filesystem.
5. **Retorno:** Retornar a lista completa de 180 nomes com a marcacao `ok x` em todos os itens.

---

## 2. Analise de Mapeamento

- **Total de questoes na lista:** 180
- **Ja verificadas pelo usuario:** 60 (21 com `imgs/` no dataset, 2 com tabelas transcritas, 37 sem solucao python no dataset ou ano diferente)
- **A verificar:** 120
  - **Coincidentes no dataset (com validacao de ano):** 53 questoes
  - **Inexistentes no dataset (sem solucao python ou ano distinto):** 67 questoes
- **Ajuste retrospectivo:** `Chuva_2019` (ano 2019) mapeado para `dataset_obi_python/Chuva` (ano 2019).
- **Total de pastas no dataset que terao imagens ao final:** 75 (21 ja existentes + 1 ajuste + 53 novas).

---

## 3. Checklist de Execucao

- [ ] Criar script de execucao e validacao deterministica em `scripts/sync_dataset_imgs.py`.
- [ ] Executar sincronizacao para as 54 questoes identificadas (53 restantes + `Chuva`).
- [ ] Validar integridade dos arquivos `problem.json` (JSON valido, campo `imgs` populado, tags presentes em `statement`).
- [ ] Executar suite de testes do projeto (`uv run pytest`) garantindo zero regressoes.
- [ ] Atualizar metricas de tokens em `.gemini/prompts/048-sincronizar-imagens-dataset-obi-python.md`.
- [ ] Apresentar ao usuario a lista integral com `ok x` formatada rigorosamente sem emotes.
