# SPEC: crawler-codigos v0.2

## Objetivo: Realizar a busca e download de soluções e códigos-fonte oficiais disponibilizados nas páginas da OBI organizados por ano e nível.

## Entidades
- CodigoSolucao { ano: int! 1999 <= ano <= 2027, nivel: str!, nome_problema: str!, linguagem: str! ['c', 'cpp', 'py', 'java', 'js', 'pas', 'zip'], url: str!, caminho_local: Path! destino `codigo/[ano]/[nivel]/[nome_arquivo]` }
- CodigoCrawlerConfig { pasta_base: Path! padrão `codigo/`, timeout: int! padrão 15, delay_requests: float! padrão 0.5, extensoes_validas: list[str]! ['.c', '.cpp', '.py', '.java', '.pas', '.js', '.zip'] }

## Pré-condições
PC1: Conexão ativa com a internet para as páginas históricas da OBI.
PC2: Diretório `codigo/` disponível para criação de pastas e escrita de arquivos.

## Regras
R1: Se a página contiver links de soluções oficiais ou códigos de programas de exemplo -> Efetua o download do arquivo no diretório correspondente.
R2: Se o arquivo de código já existir no disco local -> Pula a requisição de download.
R3: Sanitizar o nome do arquivo para garantir compatibilidade com o sistema de arquivos local.
R4: Pausa mínima de 0.5s entre downloads consecutivos.

## Exemplo (User stories)
E1: Dado que o ano 2022 disponibiliza soluções oficiais em C++ Quando o crawler é executado Então baixa os arquivos para `codigo/2022/[nivel]/[problema].cpp`.
E2: Dado que o arquivo `codigo/2022/[nivel]/[problema].cpp` já existe localmente Quando o crawler o detecta Então não realiza novo download.

## Invariantes (o que nunca pode quebrar)
I1: Arquivos de código de solução nunca devem sobrescrever ou se misturar com cadernos de enunciado ou arquivos de teste.

## Fora do escopo
- Não compilar nem executar os códigos de solução.
- Não validar a corretude ou performance das soluções.
