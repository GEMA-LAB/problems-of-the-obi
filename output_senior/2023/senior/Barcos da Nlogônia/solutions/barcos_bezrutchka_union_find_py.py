#! /usr/bin/env python3

# OBI 2023 - Fase 2
# Barcos - Solução com Union-Find e Small-To-Large
# Mateus Bezrutchka

# -- Ideia --
# Começando sem nenhuma aresta (barco), vamos adicionar as arestas em
# ordem decrescente de capacidade: se os vertices (ilhas) A e B se
# tornam conectados ao inserirmos uma aresta de capacidade CAP, então:
# - não existe caminho de A pra B com capacidade mínima maior que CAP
# - existe caminho de A pra B com capacidade mínima igual a CAP
# E portanto a resposta da consulta pro par (A, B) é CAP.

# Essa observação leva a uma solução offline (i.e. em que lemos todas as
# consultas antes de responder alguma): em cada vértice, guardamos os
# indices das consultas que incluem aquele vértice como inicio ou fim,
# e uma consulta é respondida quando a aresta adicionada torna os seus
# vertices conectados.

# -- Union-Find (DSU) --
# Precisamos de uma estrutura que nos permita:
# - guardar, para cada componente, a lista de consultas ainda não
#   respondidas que contém vértices desse componente;
# - unir duas componentes, e checar quais consultas são respondidas
#   com a união atual.
# Isso pode ser feito com Union-Find (também conhecido como DSU)
# onde cada componente guarda, além dos campos usuais, um set de todas
# as consultas inclusas.

# Qualquer implementação razoável dessa ideia é suficiente para os
# conjuntos de testes em que N é pequeno ou C = 1, mas pro caso geral
# precisamos garantir que as uniões de sets de consultas sejam eficientes.

# -- Small to Large --
# Para conseguir unir os sets de consultas de maneira eficiente,
# usamos a técnica geral conhecida como "Small to Large":
# ao processar uma série de uniões de sets, sempre inserimos os
# elementos do menor set no maior set (e não o contrário).
# Dessa forma, cada vez que um elemento é movido de set, o tamanho do
# set em que ele se encontra no mínimo dobra, e portanto para C elementos
# cada elemento é movido no máximo log C vezes. No total, são O(C log C)
# inserções em set.

# Incluindo a ordenação das arestas e o Union-Find, a complexidade final é
# O(B log B + B * UF + C log C * S)
# onde UF é a complexidade do Union-Find e S é o tempo amortizado das
# operações em set (rápido o suficiente para o nosso caso).


def read_int():
  return int(input())

def read_int_list():
  return [int(x) for x in input().split()]

n, b = read_int_list()
edges = [read_int_list() for i in range(b)]
c = read_int()
queries = [read_int_list() for i in range(c)]


# union-find init
parent = [i for i in range(n + 1)]
depth = [0 for i in range(n + 1)]
queries_in_node = [set() for i in range(n + 1)] # consultas ainda nao respondidas no componente
answer = [-1 for i in range(c)] # vai guardar as respostas das consultas


def dsu_find(x):
  if parent[x] == x:
    return x
  parent[x] = dsu_find(parent[x]) # path compression
  return parent[x]


def dsu_merge(v, w, cap):
  v = dsu_find(v)
  w = dsu_find(w)
  if v == w:
    return

  # union by rank
  if depth[v] < depth[w]:
    v, w = w, v
  parent[w] = v
  if depth[v] == depth[w]:
    depth[v] += 1

  # small-to-large sets merge
  swapped = False
  if len(queries_in_node[v]) < len(queries_in_node[w]):
    v, w = w, v
    swapped = True

  for q_id in queries_in_node[w]:
    if q_id in queries_in_node[v]:
      # acabei de encontrar a resposta pra consulta com indice q_id
      queries_in_node[v].remove(q_id)
      answer[q_id] = cap
    else:
      # ainda nao encontrei o outro vertice da consulta q_id
      queries_in_node[v].add(q_id)
  queries_in_node[w].clear()

  if swapped:
    queries_in_node[v], queries_in_node[w] = queries_in_node[w], queries_in_node[v]


def solve():
  # coloca as consultas nos sets corretos
  for i in range(c):
    x, y = queries[i]
    queries_in_node[x].add(i)
    queries_in_node[y].add(i)

  # processa arestas ordenadas de maior pra menor capacidade
  edges.sort(key=lambda x: -x[2])
  for edge in edges:
    [v, w, cap] = edge
    dsu_merge(v, w, cap)

# imprime resposta
solve()
for i in range(c):
  print(answer[i])
