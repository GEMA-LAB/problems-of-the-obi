# SPEC: crawler-cadernos v0.1

## Objetivo: Realizar o download automático e idempotente de todos os cadernos de provas da OBI em formato PDF organizados por ano e nível.

## Entidades
- CadernoPDF { ano: int! 1999 <= ano <= 2026, nivel: str! valor entre ['pj', 'p1', 'p2', 'senior', 'geral'], url: str! url pública válida do site da OBI, caminho_local: Path! destino `cadernos/[ano]/[nivel]/[nome_arquivo].pdf` }
- CrawlerConfig { pasta_base: Path! padrão `cadernos/`, timeout: int! padrão 15, delay_requests: float! padrão 0.5, padroes_url: list[str]! }

## Pré-condições
PC1: Conexão ativa com a internet para acessar as URLs base em `https://olimpiada.ic.unicamp.br/passadas/`.
PC2: Diretório base `cadernos/` com permissão de criação e escrita no sistema de arquivos.

## Regras
R1: Se o arquivo PDF já existir no caminho local de destino -> Pula a requisição de download e registra como já existente (idempotência).
R2: Se a requisição HTTP da página de listagem retornar status diferente de 200 -> Pula o padrão atual de URL e prossegue para o próximo.
R3: A cada download concluído com sucesso -> Aguardar pausa configurável (mínimo 0.5s) para não sobrecarregar o servidor da Unicamp.
R4: Se a URL da prova contiver indicação de fase ou nível (ex: `fase1`, `fase2`, `fase3`, `pj`, `p1`, `p2`) -> Inferir a pasta de nível correspondente; caso contrário, utilizar `geral`.
R5: Se o download falhar por erro de conexão ou timeout -> Registrar erro no log e continuar a execução sem abortar o crawler.

## Exemplo (User stories)
E1: Dado que o ano 2024 possui cadernos em `fase1/programacao/cadernos/` Quando o crawler é executado Então faz o download dos PDFs salvando em `cadernos/2024/fase1/[arquivo].pdf`.
E2: Dado que o arquivo `cadernos/2023/fase1/caderno_pj.pdf` já se encontra salvo em disco Quando o crawler o identifica novamente Então o arquivo não é baixado de novo.

## Invariantes (o que nunca pode quebrar)
I1: Nenhum arquivo em disco é sobrescrito ou truncado por um download falho.
I2: Toda requisição HTTP deve obrigatoriamente ter timeout explícito definido (máximo 15s).

## Fora do escopo
- Não processar o conteúdo interno dos PDFs nem chamar APIs de LLM.
- Não baixar gabaritos ou arquivos compactados em `.zip`.
