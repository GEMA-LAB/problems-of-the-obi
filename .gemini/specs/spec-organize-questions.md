# SPEC: organize-questions v0.2

## Objetivo: Realizar a correspondência, extração e organização padronizada tanto dos casos de teste (pares de entrada/saída) quanto dos códigos de soluções oficiais na estrutura de diretórios de cada questão em `output_question_obi/`, expurgando resíduos e questões inválidas.

## Entidades
- QuestionFolder { path: Path! caminho da pasta da questão contendo `problem.json`, ano: int! 1999 <= ano <= 2027, nivel: str! identificador do nível da prova, titulo: str! título original do problema, titulo_normalizado: str! slug normalizado para correspondência }
- TestCasePair { id: int! sequencial iniciado em 1, input_file: Path! arquivo de entrada terminando em `.in`, output_file: Path! arquivo de saída correspondente terminando em `.out` }
- TestCaseSource { path_zip: Path! arquivo compactado (.zip) contendo os casos de teste em `gabaritos/`, ano: int!, nivel: str!, nome_normalizado: str! }
- SolutionSource { path_arquivo: Path! arquivo de código ou zip em `codigo/`, ano: int!, nivel: str!, nome_normalizado: str!, linguagem: str! extensão suportada }
- OrganizeConfig { pasta_output: Path! padrão `output_question_obi/` ou `output/`, pasta_gabaritos: Path! padrão `gabaritos/`, pasta_codigo: Path! padrão `codigo/`, force: bool! padrão False }
- OrganizeResult { questao: str!, test_pairs: list[TestCasePair]!, solutions_count: int! quantidade de arquivos de solução copiados, status: str! ['sucesso', 'parcial', 'sem_recursos'] }

## Pré-condições
PC1: Diretórios das questões criados em `output_question_obi/` (ou `output/`) contendo `problem.json` com metadados obrigatórios (título, ano e nível).
PC2: Diretórios `gabaritos/` e `codigo/` acessíveis contendo os arquivos previamente baixados pelos crawlers.
PC3: Permissão de leitura nos diretórios de origem e permissão de escrita e exclusão nos diretórios das questões.

## Regras
R1: A correspondência entre a pasta da questão e os arquivos de gabarito (`gabaritos/`) e soluções (`codigo/`) DEVE utilizar normalização Unicode estrita (NFD, remoção de diacríticos/acentos, pontuações, espaços e case-folding).
R2: Se existir arquivo ZIP de gabarito correspondente em `gabaritos/` -> Descompacta os casos de teste na subpasta `test_cases/` da respectiva questão.
R3: Se a subpasta `test_cases/` da questão já contiver casos de teste válidos e `force=False` -> Pula a descompactação para garantir idempotência estrita.
R4: Todos os casos de teste extraídos DEVEM ser normalizados em pares consistentes `[numero].in` e `[numero].out` com numeração sequencial iniciada em 1, alocados sob `test_cases/inputs/` e `test_cases/outputs/` (ou diretamente em `test_cases/`).
R5: Todos os arquivos e subdiretórios que não correspondam aos pares de teste normalizados (como executáveis compilados `.exe`, `.o`, arquivos temporários ou lixo residual) DEVEM ser excluídos de `test_cases/`.
R6: Se existirem arquivos de soluções oficiais em `codigo/` (arquivos de código-fonte ou arquivos `.zip` de soluções) correspondentes à questão -> Copia/extrai todos os arquivos de solução pertinentes para a subpasta `solutions/` da respectiva questão.
R7: Se após a tentativa de processamento a pasta da questão em `output_question_obi/` não possuir casos de teste válidos (`test_cases/` vazio ou sem pares válidos) -> A pasta da questão DEVE ser removida do dataset ou sinalizada como sem testes para manter a consistência da base.
R8: Se um arquivo ZIP de gabarito estiver corrompido ou se não houver soluções oficiais disponíveis para a questão -> Registra no log de auditoria e prossegue para as demais questões sem interromper a pipeline.
R9: O CLI deve suportar a invocação da etapa via argumento `--step organize-questions` (mantendo compatibilidade e alias para `--step organize-testcases`), além de aceitar filtros opcionais por `--ano` e `--nivel`.

## Exemplo (User stories)
E1: Dado que a questão "Cabo de Guerra" de 2023 nível "PJ" existe em `output_question_obi/2023/pj/Cabo de Guerra/` com `problem.json` e existem `gabaritos/2023/pj/Cabo de guerra.zip` e `codigo/2023/pj/cabo.java` Quando o comando `organize-questions` é executado Então descompacta e normaliza os testes gerando `1.in`, `1.out`, `2.in`, `2.out` em `test_cases/`, copia `cabo.java` para `solutions/` e limpa arquivos residuais.
E2: Dado que a pasta da questão já possui `test_cases/` normalizados e `solutions/` populados Quando `organize-questions` é executado sem flag `--force` Então mantém os arquivos existentes intactos e pula o processamento.
E3: Dado que uma questão em `output_question_obi/` não possui nenhum caso de teste associado em `gabaritos/` Quando a etapa de organização e limpeza é concluída Então remove a pasta da questão para que apenas problemas completos com testes permaneçam no dataset.

## Invariantes (o que nunca pode quebrar)
I1: O arquivo `problem.json` e as eventuais imagens da questão (`imgs/`) nunca devem ser apagados, sobrescritos ou corrompidos.
I2: Para todo arquivo de entrada `k.in` deve existir estritamente seu par de saída `k.out` correspondente (correlação biunívoca).
I3: Casos de teste (`test_cases/`) e códigos de solução (`solutions/`) devem residir estritamente em suas respectivas subpastas isoladas, sem misturar código-fonte com dados de teste.
I4: Nenhuma questão sem casos de teste válidos deve permanecer no dataset final consolidado.

## Fora do escopo
- Não realizar download de arquivos da internet (atribuição dos crawlers).
- Não gerar casos de teste sintéticos ou artificiais via LLM.
- Não compilar nem executar os códigos de solução contra os casos de teste.
- Não alterar metadados semânticos do enunciado em `problem.json`.
