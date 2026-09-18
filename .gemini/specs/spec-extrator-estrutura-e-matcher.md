# SPEC: extrator-estrutura-e-matcher v0.1

## Objetivo: Padronizar a hierarquia de diretórios do extrator LLM para espelhar rigorosamente a estrutura de `cadernos/` (eliminando pastas espúrias como `n1`) e implementar correspondência heurística flexível e resiliente entre os códigos de solução oficiais em `codigo/[ano]/[nivel]/` e as questões em `output_with_code/[ano]/[nivel]/`.

## Entidades
- CadernoOrigem { path: Path! caminho absoluto do arquivo PDF sob `cadernos/`, ano: int! 1999 <= ano <= 2027 derivado do diretório do caderno, nivel: str! valor canônico entre ['pj', 'p1', 'p2', 'senior', 'geral'] derivado do subdiretório do caderno }
- QuestionDestination { path_base: Path! caminho da pasta da questão no formato `output_with_code/[ano]/[nivel]/[nome_questao]/`, problem_json: Path! arquivo `problem.json` dentro de `path_base/`, ano: int! obrigatoriamente idêntico ao ano do CadernoOrigem, nivel: str! obrigatoriamente idêntico ao nível do CadernoOrigem, titulo_sanitizado: str! nome limpo sem caracteres proibidos pelo sistema de arquivos }
- SolutionCandidate { path_arquivo: Path! caminho do arquivo de código ou zip sob `codigo/[ano]/[nivel]/`, ano: int!, nivel: str!, stem_original: str! nome base sem extensão, prefixo_problema: str! identificador extraído antes do primeiro separador (`_` ou `-`), tokens: list[str]! tokens de palavras significativas sem stopwords, linguagem: str! extensão mapeada }
- MatchHeuristicResult { questao: str!, question_path: Path!, solutions_matched: list[SolutionCandidate]!, criterio_correspondencia: str! ['exato', 'prefixo_separador', 'slug_reverso', 'intersecao_tokens'] }

## Pré-condições
PC1: Cadernos de provas em formato PDF devidamente organizados em disco sob o padrão `cadernos/[ano]/[nivel]/[nome_arquivo].pdf`.
PC2: Arquivos de código-fonte de soluções oficiais baixados e organizados sob `codigo/[ano]/[nivel]/[arquivo_solucao].[ext]` (onde nível coincide com a estrutura da OBI).
PC3: Extrator OpenAI configurado e operacional com acesso ao diretório base de saída `output_with_code/`.

## Regras
R1: A hierarquia de pastas de destino para cada questão extraída DEVE espelhar estritamente a localização relativa do caderno PDF de origem (`cadernos/[ano]/[nivel]/...` -> `output_with_code/[ano]/[nivel]/[nome_questao]/`). O extrator NUNCA deve inferir ou criar o nível do diretório de saída com base na resposta de texto da LLM (como `n1`), devendo utilizar unicamente a estrutura de diretórios do caderno de origem.
R2: Ao persistir o arquivo `problem.json`, os metadados `year` e `level` DEVEM ser validados e normalizados contra os valores canônicos derivados da pasta do caderno de origem (`pj`, `p1`, `p2`, `senior`, `geral`), garantindo consistência semântica entre os metadados do JSON e o caminho em disco.
R3: Se existirem diretórios legados inconsistentes em `output_with_code/` (como `output_with_code/2025/n1/`) -> Realizar a migração automática das pastas de questões para o nível correto identificado em `cadernos/` (ex: `output_with_code/2025/p1/`) e remover as pastas vazias órfãs (`n1`).
R4: A busca por códigos de solução oficial para uma questão (`output_with_code/[ano]/[nivel]/[nome_questao]`) DEVE ter como escopo primário e obrigatório o diretório correspondente `codigo/[ano]/[nivel]/`, aplicando busca complementar em `codigo/[ano]/` e `codigo/[ano]/geral/` apenas se nenhuma solução for encontrada no nível primário.
R5: A correspondência entre os arquivos de solução em `codigo/[ano]/[nivel]/` e as questões NÃO DEVE exigir igualdade total de nomes, devendo aceitar como correspondência positiva qualquer um dos seguintes critérios heurísticos ordenados por especificidade:
  - R5.1 (Exatidão Normalizada): O slug normalizado do nome do arquivo (sem extensão) é idêntico ao slug normalizado do título da questão (ex: `diagonal.java` == `Diagonal`).
  - R5.2 (Prefixo por Separador): O prefixo do nome do arquivo antes do primeiro separador (`_` ou `-`), normalizado, é idêntico ao slug do título da questão ou à primeira palavra significativa do título (ex: `recarga_carro.cpp` e `recarga_lobo_bb.cpp` associam-se a `Recarga`; `redes_1_freq_java.java` e `redes_andre.cpp` associam-se a `Redes de Descanso`; `cabo_carol.py` associa-se a `Cabo de Guerra`; `fila_c.c` e `fila_cpp.cpp` associam-se a `Fila`).
  - R5.3 (Slug Reverso / Substring de Prefixo): O slug normalizado do arquivo começa com o slug normalizado da questão (`stem_norm.startswith(target_slug)`), contemplando nomes com variações sem separador (ex: `recargacarro` -> `recarga`).
  - R5.4 (Interseção de Tokens Significativos): O nome do arquivo contém todos os tokens significativos do título da questão, ignorando stopwords (`de`, `da`, `do`, `dos`, `das`, `e`, `com`, `para`, `em`, `a`, `o`) e termos auxiliares técnicos (`solucao`, `reference`, `aluno`, `cpp`, `py`, `java`, `js`, `andre`, `bez`, `sorting`) (ex: `feira_artesanato_cpp.cpp` e `feira.java` associam-se a `Feira de Artesanato`; `mania_aluno.py` e `mania_matriz_cpp.cpp` associam-se a `Mania de Ímpar`).
R6: Se um arquivo de solução atender a critérios de correspondência para mais de uma questão no mesmo nível -> Atribuir o arquivo à questão que apresentar o maior número de tokens coincidentes ou prefixo mais longo e específico (ex: `fila_cantina.cpp` associa-se a `Fila na Cantina`, enquanto `fila.java` associa-se a `Fila`).
R7: Todos os arquivos de código de solução correspondentes DEVEM ser copiados para a subpasta `solutions/` da respectiva questão (`output_with_code/[ano]/[nivel]/[nome_questao]/solutions/`), preservando seus nomes e extensões de arquivo originais.

## Exemplo (User stories)
E1: Dado que o caderno PDF da Fase 1 P1 de 2025 está salvo em `cadernos/2025/p1/ProvaOBI2025_f1p1.pdf` contendo as questões "Café com Leite", "Fila" e "Pizzaria" Quando o extrator LLM processa o PDF Então as questões são salvas em `output_with_code/2025/p1/Café com Leite/`, `output_with_code/2025/p1/Fila/` e `output_with_code/2025/p1/Pizzaria/`, sem criar a pasta espúria `output_with_code/2025/n1/`.
E2: Dado que a questão "Redes de Descanso" reside em `output_with_code/2025/p1/Redes de Descanso/` e a pasta `codigo/2025/p1/` contém `redes_1_freq_java.java`, `redes_2_dict_py.py`, `redes_andre.cpp` e `redes_reference.cpp` Quando o organizador busca soluções para essa questão Então identifica os arquivos pelo prefixo `redes` e copia todos para `output_with_code/2025/p1/Redes de Descanso/solutions/`.
E3: Dado que a questão "Recarga" reside em `output_with_code/2025/p1/Recarga/` e a pasta `codigo/2025/p1/` contém `recarga_carro.cpp`, `recarga_lobo_bb.cpp` e `recarga_pedro_union_find.cpp` Quando o matcher avalia os arquivos Então associa os códigos pelo prefixo `recarga` e popula `solutions/`.
E4: Dado que o dataset atual contém a pasta `output_with_code/2025/n1/` com as questões de 2025 P1 Quando a rotina de saneamento é executada Então move as pastas das questões para `output_with_code/2025/p1/`, preservando seu conteúdo e excluindo o diretório `n1`.

## Invariantes (o que nunca pode quebrar)
I1: A árvore de diretórios em `output_with_code/` DEVE ser estritamente isomórfica à de `cadernos/` no tocante aos níveis de ano e prova (`[ano]/[nivel]`), sem criação de níveis inexistentes na origem.
I2: Nenhum código de solução oficial deve ser copiado para pastas de questões de outros anos ou de outros níveis sem correlação válida.
I3: O conteúdo do enunciado em `problem.json` e os casos de teste em `test_cases/` nunca devem ser corrompidos, sobrescritos ou apagados durante a associação e cópia de soluções.

## Fora do escopo
- Não renomear internamente nem alterar a sintaxe ou o conteúdo dos códigos de solução oficiais.
- Não compilar, interpretar ou avaliar os códigos de solução contra os casos de teste da questão.
- Não alterar a lógica de download de PDFs de cadernos ou de gabaritos em zip.
