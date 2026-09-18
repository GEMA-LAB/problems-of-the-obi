# SPEC: extractor-llm v0.3

## Objetivo: Processar cadernos de provas da OBI em formato PDF utilizando a biblioteca oficial da OpenAI para extrair os problemas de programação em formato JSON estruturado, interpretando limites de tempo e memória calibrados para a linguagem Python e salvando em `output_with_code/[ano]/[nivel]/[nome_questao]/problem.json`.

## Entidades
- ProblemSchema { title: str! não vazio, statement: str! descrição completa do enunciado mantendo quebras de linha com `\n`, input: str! texto da seção de Entrada, output: str! texto da seção de Saída, constraints: str! texto da seção de Restrições, examples: list[Exemplo]! lista de exemplos de entrada e saída, imgs: list[str]! links ou caminhos de imagens associadas, rating: list[int]! pontuação das subtarefas, year: str! ano de 4 dígitos, level: str! ['PJ', 'P1', 'P2', 'Senior', 'Geral'], period: str! fase da prova (ex: 'Fase 1', 'Fase 2', 'Fase 3'), topics: list[str]! tópicos e categorias da questão, time_limit: float! tempo limite em segundos calibrado para resolução em Python, memory_limit: int! limite de memória em MB calibrado para resolução em Python }
- Exemplo { input: str!, output: str! }
- ExtractorConfig { base_url: str! URL base da API OpenAI (padrão `https://api.openai.com/v1` ou endpoint compatível), api_key: str! chave de acesso da API, model: str! nome do modelo (ex: `gpt-4o-mini`), pasta_entrada: Path! diretório dos cadernos PDF (`cadernos/` ou `data/`), pasta_output: Path! diretório base de saída (`output_with_code/`) }

## Pré-condições
PC1: Variáveis de ambiente configuradas no arquivo `.env` focadas estritamente na biblioteca OpenAI: `OPENAI_BASE_URL`, `OPENAI_API_KEY` e `OPENAI_MODEL`.
PC2: Arquivos de cadernos de prova em formato PDF disponíveis no diretório de entrada (`cadernos/` ou `data/`).
PC3: Biblioteca `openai` instalada no ambiente virtual gerenciado via `uv`.

## Regras
R1: A extração de problemas DEVE utilizar a biblioteca oficial `openai.OpenAI`, inicializada com `base_url` e `api_key` definidos no `.env`.
R2: O envio do PDF para a API da OpenAI DEVE utilizar a Files API nativa (`client.files.create(file=f, purpose="assistants")`) e a requisição do modelo DEVE enviar a referência do arquivo carregado junto ao prompt de extração.
R3: O prompt de extração DEVE instruir a LLM a interpretar o `time_limit` (float, em segundos) e o `memory_limit` (int, em MB) especificamente com foco na resolução da questão na linguagem Python a partir do enunciado e restrições fornecidas, e NÃO DEVE conter nem extrair o campo `difficulty`.
R4: Se a resposta da LLM contiver formatações markdown (como blocos ```json ... ```) ou texto antes/depois do JSON -> Sanitizar o texto extraindo puramente o array JSON antes da desserialização com `json.loads`.
R5: Se a resposta da LLM não for um JSON válido ou não for uma lista de objetos -> Registrar o erro, adicionar o PDF à lista de falhas para repetição cíclica e continuar a execução.
R6: Para cada problema extraído com sucesso, criar a pasta `output_with_code/[ano]/[nivel]/[nome_questao]/` e salvar os dados em `problem.json` com indentação de 4 espaços (`indent=4`) e `ensure_ascii=False`.
R7: A hierarquia de diretórios DEVE organizar os problemas isoladamente por `[ano]` e `[nivel]` (em letras minúsculas: `pj`, `p1`, `p2`, `senior`, `geral`), sanitizando caracteres especiais do nome da questão (como remoção de `?`).
R8: Ao término do processamento de cada PDF (tanto em caso de sucesso quanto em caso de erro ou exceção) -> O arquivo remoto enviado para a OpenAI DEVE ser obrigatoriamente excluído dos servidores (`client.files.delete`) no bloco `finally`.

## Exemplo (User stories)
E1: Dado um arquivo PDF `cadernos/2024/pj/ProvaOBI2024_f3pj.pdf` contendo problemas da Fase 3 Quando o extrator da OpenAI processa o documento Então cria as pastas em `output_with_code/2024/pj/[nome_questao]/` com o `problem.json` contendo `time_limit` e `memory_limit` interpretados para Python e sem o campo `difficulty`.
E2: Dado que existem problemas homônimos em anos ou níveis distintos (ex: "Relógio" em 2024 nível PJ e em 2012 nível P1) Quando processados Então são organizados naturalmente em pastas separadas `output_with_code/2024/pj/Relogio/` e `output_with_code/2012/p1/Relogio/` sem sobreposição.
E3: Dado que ocorre uma exceção de parsing ou timeout durante a requisição Quando a execução passa pelo bloco `finally` Então o arquivo temporário é deletado da OpenAI e o PDF é mantido na lista de pendências para nova tentativa.

## Invariantes (o que nunca pode quebrar)
I1: Nenhum arquivo PDF carregado na API da OpenAI deve permanecer retido após a conclusão ou falha da requisição.
I2: O arquivo `problem.json` gerado deve ser um JSON estritamente válido, contendo os campos obrigatórios com `time_limit` (float) e `memory_limit` (int) calibrados para Python, sem a presença do campo `difficulty`.
I3: A estrutura em disco DEVE respeitar rigorosamente o padrão `output_with_code/[ano]/[nivel]/[nome_questao]/problem.json`.

## Fora do escopo
- Não gerar ou armazenar classificação subjetiva de dificuldade (`difficulty`).
- Não utilizar ou depender da API ou SDK da Google (Gemini) nesta especificação focada em OpenAI.
- Não descompactar gabaritos nem normalizar casos de teste nesta etapa.
- Não executar código ou avaliar soluções.
