# SPEC: extractor-llm v0.1

## Objetivo: Processar cadernos de prova em PDF utilizando APIs de LLMs (Gemini / OpenAI) e extrair os problemas de programação em formato JSON estruturado seguindo o schema padrão.

## Entidades
- ProblemSchema { title: str! não vazio, statement: str! descrição completa mantendo quebras de linha com `\n`, input: str! seção de Entrada, output: str! seção de Saída, constraints: str! seção de Restrições, examples: list[Exemplo]! lista com entradas e saídas, imgs: list[str]! links ou caminhos de imagens associadas, rating: list[int]! pontuação das subtarefas, year: str! ano de 4 dígitos, level: str! ['PJ', 'P1', 'P2', 'Senior', 'Geral'], period: str! ex: 'Fase 1', topics: list[str]! categorias do problema, difficulty: str! ['Fácil', 'Médio', 'Difícil'] }
- Exemplo { input: str!, output: str! }
- ExtractorConfig { provider: str! ['gemini', 'openai'], model: str!, prompt_template_path: Path! padrão `src/prompts/extraction_prompt.md`, output_base_dir: Path! padrão `output_question_obi/` }

## Pré-condições
PC1: Variáveis de ambiente configuradas no `.env` (`GEMINI_API`, `GEMINI_MODEL`, ou `GPT_API`, `GPT_MODEL`).
PC2: Arquivos de cadernos de prova em formato PDF disponíveis no diretório `cadernos/`.
PC3: Template de prompt disponível e válido no sistema.

## Regras
R1: O envio do PDF para a API da LLM deve utilizar a Files API nativa correspondente (Gemini Files API ou OpenAI Files API).
R2: Se a resposta da LLM contiver blocos cercados por markdown (ex: ```json ... ```) -> Sanitizar o texto extraindo puramente a string JSON antes da desserialização.
R3: Se a resposta não for um JSON válido ou não for uma lista de objetos -> Registrar erro detalhado, salvar o PDF na lista de falhas para reprocessamento e continuar.
R4: Para cada problema extraído, salvar em `output_question_obi/[ano]/[nivel]/[nome-questao]/problem.json` com `indent=4` e `ensure_ascii=False`.
R5: Se já existir um diretório para o título da questão com ano divergente -> Adicionar sufixo `_{ano}` ao título e sanitizar caracteres especiais (ex: remover `?`).
R6: Ao término do processamento de cada PDF (com sucesso ou falha) -> O arquivo enviado deve ser obrigatoriamente deletado dos servidores remotos da API (bloco `finally`).

## Exemplo (User stories)
E1: Dado um caderno `cadernos/2024/pj/caderno.pdf` contendo 3 problemas Quando processado pela API Gemini Então cria 3 pastas em `output_question_obi/2024/pj/` contendo cada uma seu `problem.json` válido.
E2: Dado que a chamada de API retorna erro de cota ou rede Quando detectada a exceção Então o erro é capturado, o arquivo remoto é excluído no `finally` e o PDF é marcado para retry.

## Invariantes (o que nunca pode quebrar)
I1: Nenhum arquivo de caderno PDF deve permanecer retido indefinidamente nos servidores remotos da API da LLM após o término da requisição.
I2: Todo `problem.json` gerado deve possuir formato JSON estritamente válido e decodificável.

## Fora do escopo
- Não associar nem descompactar gabaritos ou casos de teste nesta etapa.
- Não executar código ou avaliar soluções.
