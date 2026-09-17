# SPEC: crawler-gabaritos v0.1

## Objetivo: Realizar a busca e download de todos os arquivos compactados (.zip) de gabaritos e casos de teste da OBI organizados por ano e nível.

## Entidades
- GabaritoZIP { ano: int! 1999 <= ano <= 2026, nivel: str! valor entre ['pj', 'p1', 'p2', 'senior', 'geral'], nome_questao: str! não vazio, url: str! url terminando em `.zip`, caminho_local: Path! destino `gabaritos/[ano]/[nivel]/[nome_arquivo_sanitizado].zip` }
- GabaritoCrawlerConfig { pasta_base: Path! padrão `gabaritos/`, timeout: int! padrão 15, delay_requests: float! padrão 0.5, termos_filtro: list[str]! ['gabarito', 'testes'] }

## Pré-condições
PC1: Conexão ativa com a internet para acessar as URLs base em `https://olimpiada.ic.unicamp.br/passadas/`.
PC2: Diretório `gabaritos/` acessível para criação e escrita.

## Regras
R1: Se o link na página terminar com `.zip` e contiver no texto visível ou na URL termos como `gabarito` ou `testes` -> Considerar como arquivo de gabarito válido para download.
R2: Se o link possuir texto visível não vazio -> Utilizar esse texto sanitizado como nome do arquivo final; caso contrário, extrair o nome do próprio arquivo da URL.
R3: O nome do arquivo salvo DEVE ser sanitizado de caracteres proibidos em sistemas de arquivos (`\ / : * ? " < > |`).
R4: Se o arquivo `.zip` correspondente já existir em disco -> Pular o download e registrar como já presente.
R5: Se o download for interrompido ou corrompido -> Excluir o arquivo residual incompleto e registrar erro no log.
R6: Pausa obrigatória de no mínimo 0.5s entre downloads consecutivos para respeitar o servidor de origem.

## Exemplo (User stories)
E1: Dado que o ano 2023 possui um link com texto "Entrevistas de Emprego" apontando para um ZIP de testes Quando o crawler executa Então baixa e salva em `gabaritos/2023/[nivel]/Entrevistas de Emprego.zip`.
E2: Dado que o arquivo `gabaritos/2023/[nivel]/Entrevistas de Emprego.zip` já existe Quando o crawler o encontra novamente Então pula o download.

## Invariantes (o que nunca pode quebrar)
I1: Apenas arquivos ZIP íntegros e não vazios são mantidos no diretório de destino.
I2: Nomes de arquivo gravados em disco nunca devem conter caracteres inválidos que causem exceção de I/O no sistema operacional.

## Fora do escopo
- Não descompactar nem extrair o conteúdo dos arquivos ZIP nesta etapa.
- Não validar ou renomear arquivos de teste internos nesta etapa.
