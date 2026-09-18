#! /usr/bin/env python3

"""
 * OBI 2023 - Fase 3
 * Metrônibus - Solução O(N + K1 + K2) com BFS e DFS
 * Mateus Bezrutchka
 * 
 * Modelamos o problema usando um grafo novo baseado no original, onde
 * cada estação vira dois vértices: um para metrô e um para ônibus, com
 * as arestas conectando somente os vértices do sistema correspondente.
 * 
 * Assim, podemos encontrar a resposta rodando uma BFS modificada nos
 * dois candidatos a vértice inicial (um de metrô e um de ônibus):
 * Toda vez que processamos um vértice na BFS, também processamos todos
 * os vértices da componente conexa dele (já que todos podem ser alcançados
 * sem pagar nada).
"""

def read_ints():
  return [int(x) for x in input().split()]

INF = int(1e9 + 10)

# 2v - 1 pra metrô, 2v pra ônibus
def vtx(s, v):
  return 2 * v - 1 + s

# o outro vértice representando a mesma estação
def other_vtx(v):
  if v % 2 == 1:
    return v + 1
  else:
    return v - 1


## Entrada ##

n, k1, k2, p = read_ints()

# 2 * n porque vamos duplicar o grafo
n = 2 * n
graph = [[] for i in range(n + 1)] # lista de adj
dist = [INF for i in range(n + 1)]
visited = [False for i in range(n + 1)]

for i in range(k1):
  u, v = read_ints()
  graph[vtx(0, v)].append(vtx(0, u))
  graph[vtx(0, u)].append(vtx(0, v))
for i in range(k2):
  u, v = read_ints()
  graph[vtx(1, v)].append(vtx(1, u))
  graph[vtx(1, u)].append(vtx(1, v))

A, B = read_ints()


## BFS + DFS ##

bfs_queue = []
q_start, q_end = 0, 0

def dfs(origin, distance):
  global bfs_queue, q_start, q_end
  dfs_stack = [origin]

  while len(dfs_stack) > 0:
    v = dfs_stack.pop()
    if visited[v]:
      continue
    visited[v] = True
    dist[v] = distance

    # coloca o outro vértice da estação na fila da BFS
    w = other_vtx(v)
    if not visited[w]:
      dist[w] = distance + 1
      bfs_queue.append(w)
      q_end += 1

    # transição da dfs
    for next_v in graph[v]:
      if not visited[next_v]:
        dfs_stack.append(next_v)


# retorna a distância mínima pra estação B
def bfs(origin):
  global bfs_queue, q_start, q_end
  for v in range(1, n + 1):
    dist[v] = INF
    visited[v] = False

  bfs_queue = [origin]
  q_start, q_end = 0, 1
  dist[origin] = 1

  while q_start < q_end:
    v = bfs_queue[q_start]
    q_start += 1
    dfs(v, dist[v])

  return min(dist[vtx(0, B)], dist[vtx(1, B)])


mresp = bfs(vtx(0, A)) # começando no metro
oresp = bfs(vtx(1, A)) # começando no onibus
if mresp == INF and oresp == INF:
  print(-1)
else:
  print(min(mresp, oresp) * p)
