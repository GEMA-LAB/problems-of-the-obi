# SPEC: organize-questions v0.1

## Objetivo: Cruzar e organizar tanto os casos de teste (.zip de gabaritos) quanto os códigos de soluções oficiais na estrutura de diretórios de cada questão respectiva.

## Entidades
- QuestionFolder { path: Path! caminho da pasta da questão contendo problem.json, ano: int! 1999 <= ano <= 2027, nivel: str! identificador do nível da prova, titulo: str! título original do problema, titulo_normalizado: str! slug normalizado para correspondência }
- TestCaseSource { path_zip: Path! arquivo compactado (.zip) contendo os casos de teste em gabaritos/, ano: int!, nivel: str!, nome_normalizado: str! }
- SolutionSource { path_arquivo: Path! arquivo de código ou zip de códigos em codigo/, ano: int!, nivel: str!, nome_normalizado: str!, linguagem: str! extensão suportada }
- OrganizeResult { questao: str!, test_cases_organizados: bool!, solutions_organizadas: int! quantidade de arquivos de solução copiados, status: str! ['sucesso', 'parcial', 'sem_recursos'] }
- OrganizeConfig { pasta_output: Path! padrão output_question_obi/ ou output/, pasta_gabaritos: Path! padrão gabaritos/, pasta_codigo: Path! padrão codigo/, force: bool! padrão False }

## Pré-condições
PC1: As pastas das questões extraídas devem existir no diretório de saída (output_question_obi/ ou output/) contendo o arquivo problem.json com metadados (título, ano e nível).
PC2: Os diretórios gabaritos/ e codigo/ devem estar acessíveis contendo os arquivos baixados pelo crawler.
PC3: Permissão de leitura nos diretórios de origem e escrita no diretório de destino de cada questão.

## Regras
R1: Se existir um arquivo ZIP de gabarito correspondente ao ano, nível e nome normalizado da questão em gabaritos/ -> Descompacta os casos de teste na subpasta test_cases/ da respectiva questão.
R2: Se a subpasta test_cases/ da questão já contiver arquivos e force=False -> Pula a descompactação para evitar sobrescrita ou processamento redundante (idempotência).
R3: Se existirem arquivos de soluções oficiais em codigo/ correspondentes ao ano, nível e identificador/slug normalizado da questão -> Copia todos os arquivos de solução correspondentes para a subpasta solutions/ da respectiva questão.
R4: Se o arquivo de código em codigo/ for um pacote compactado (.zip) contendo soluções da questão -> Descompacta apenas os arquivos de solução pertinentes na subpasta solutions/ da questão.
R5: A correspondência entre a questão e seus gabaritos e soluções deve utilizar normalização Unicode estrita (NFD, remoção de diacríticos, pontuações, espaços e case-folding), com suporte a correspondência por slug e prefixo.
R6: Se um arquivo ZIP de gabarito estiver corrompido ou ilegível -> Registra o erro de integridade sem abortar o processamento das demais questões.
R7: Se não for encontrado gabarito ou solução para uma determinada questão -> Registra o status parcial ou ausente e prossegue para a próxima questão sem falhar a pipeline.
R8: O CLI deve suportar a invocação da etapa via argumento --step organize-questions (mantendo compatibilidade transitória com o comando legado organize-testcases), além de filtros opcionais por --ano e --nivel.

## Exemplo (User stories)
E1: Dado que a questão "Cabo de Guerra" de 2023 nível "PJ" possui pasta em output_question_obi/2023/pj/Cabo de Guerra/ com problem.json e existem gabaritos/2023/pj/Cabo de guerra.zip e codigo/2023/pj/cabo.java, cabo_andre.cpp Quando organize-questions é executado Então descompacta os testes em output_question_obi/2023/pj/Cabo de Guerra/test_cases/ e copia os códigos para output_question_obi/2023/pj/Cabo de Guerra/solutions/.
E2: Dado que a pasta da questão já possui test_cases/ e solutions/ populados Quando organize-questions é executado sem flag --force Então mantém os arquivos existentes intactos e pula a extração.
E3: Dado que uma questão possui gabarito disponível mas não possui códigos de solução oficiais em codigo/ Quando organize-questions é executado Então descompacta os casos de teste, registra a ausência de soluções e conclui com status parcial.

## Invariantes (o que nunca pode quebrar)
I1: O arquivo problem.json e as imagens da questão (imgs/) nunca devem ser apagados, sobrescritos ou corrompidos pela etapa de organização.
I2: Os arquivos de gabarito (test_cases/) e soluções oficiais (solutions/) devem residir estritamente em suas respectivas subpastas dentro da questão, sem misturar código-fonte com entradas/saídas de teste.
I3: Soluções de uma questão nunca devem ser alocadas na pasta de outra questão divergente.

## Fora do escopo
- Não realizar download de arquivos da internet (função do crawler).
- Não normalizar nem renomear arquivos internos de casos de teste para o formato final [numero].in e [numero].out (função do módulo cleaner/normalizer de test cases).
- Não compilar nem executar os códigos de solução.
- Não invocar APIs de LLM nem alterar metadados em problem.json.
