# SPEC: processor-testcases v0.1

## Objetivo: Associar arquivos de gabarito (.zip) às questões extraídas, descompactar os casos de teste, padronizar para pares [numero].in e [numero].out e remover resíduos e questões inválidas.

## Entidades
- TestCasePair { id: int! sequencial iniciado em 1, input_file: Path! terminando em `.in`, output_file: Path! terminando em `.out` correspondente }
- QuestionDirectory { path: Path! caminho da pasta da questão em `output_question_obi/`, problem_json: Path! arquivo de metadados, test_cases_dir: Path! pasta de testes, test_pairs: list[TestCasePair] }
- MatcherResult { nome_questao_normalizado: str!, nome_zip_normalizado: str!, match_encontrado: bool!, arquivo_zip: Path!, pasta_destino: Path! }

## Pré-condições
PC1: Diretórios de questões criados em `output_question_obi/` contendo `problem.json`.
PC2: Arquivos `.zip` de gabaritos baixados presentes em `gabaritos/`.

## Regras
R1: A correspondência entre o nome da pasta da questão e o arquivo ZIP de gabarito deve ser realizada por normalização de texto Unicode (NFD, remoção de diacríticos/acentos, pontuações, espaços e case-folding).
R2: Se a correspondência for encontrada e a pasta `test_cases/` da questão estiver vazia -> Descompactar o `.zip` diretamente em `test_cases/` e deletar o arquivo ZIP original para economizar espaço em disco.
R3: Renomear e estruturar todos os arquivos de entrada para `[numero].in` e os arquivos de saída/solução correspondentes para `[numero].out` (dentro de `inputs/` ou diretamente em `test_cases/`), mantendo numeração 1 a N consistente.
R4: Todos os arquivos e subdiretórios que não correspondam aos testes normalizados (como executáveis compilados, arquivos temporários ou arquivos não reconhecidos) devem ser excluídos.
R5: Se uma pasta de questão em `output_question_obi/` não possuir casos de teste válidos ou contiver apenas resíduos após o processamento -> A pasta da questão deve ser removida do dataset ou sinalizada como inválida.

## Exemplo (User stories)
E1: Dado que a questão "Entrevistas de Emprego" existe em `output_question_obi/2023/fase1/Entrevistas de Emprego` e o arquivo `gabaritos/2023/fase1/Entrevistasdeemprego.zip` existe Quando o processador é executado Então descompacta e normaliza os testes gerando `1.in`, `1.out`, `2.in`, `2.out`, removendo resíduos e o arquivo ZIP.
E2: Dado que uma questão em `output_question_obi/` não possui nenhum caso de teste associado Quando a etapa de limpeza é executada Então remove a pasta da questão para manter apenas questões válidas no dataset.

## Invariantes (o que nunca pode quebrar)
I1: Para todo arquivo de entrada `k.in` deve existir estritamente seu par de saída `k.out` correspondente.
I2: Nenhuma questão sem casos de teste válidos deve permanecer no dataset final consolidado.

## Fora do escopo
- Não gerar casos de teste sintéticos ou artificiais via LLM.
- Não executar as soluções contra os casos de teste.
