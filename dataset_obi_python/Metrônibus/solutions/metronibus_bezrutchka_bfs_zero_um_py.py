#! /usr/bin/env python3

"""
 * OBI 2023 - Fase 3
 * Metrônibus - Solução O(N + K1 + K2) com BFS 0-1
 * Mateus Bezrutchka
 *
 * Modelamos o problema usando um grafo novo baseado no original:
 * - Cada estação vira dois vértices: um para metrô e um para ônibus;
 * - Cada ligação vira uma aresta com peso 0 entre os vértices do
 *   respectivo sistema;
 * - Adicionamos uma aresta de peso 1 entre os dois vértices representando
 *   a mesma estação.
 *
 * Dessa forma, o número mínimo de trocas de sistema é o tamanho do caminho
 * mínimo entre um dos vértices de início (temos 2) e um dos vértices de fim.
 *
 * Esse caminho mínimo pode ser encontrado usando BFS 0-1.
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



n, k1, k2, p = read_ints()

# 2 * n porque vamos duplicar o grafo
n = 2 * n
graph = [[] for i in range(n + 1)] # lista de adj (vertice, distancia)
dist = [INF for i in range(n + 1)]
visited = [False for i in range(n + 1)]

for i in range(k1):
  u, v = read_ints()
  graph[vtx(0, v)].append((vtx(0, u), 0))
  graph[vtx(0, u)].append((vtx(0, v), 0))
for i in range(k2):
  u, v = read_ints()
  graph[vtx(1, v)].append((vtx(1, u), 0))
  graph[vtx(1, u)].append((vtx(1, v), 0))

A, B = read_ints()


# adiciona arestas de peso 1
for v in range(1, n // 2 + 1):
  graph[vtx(0, v)].append((vtx(1, v), 1))
  graph[vtx(1, v)].append((vtx(0, v), 1))


# retorna a distância mínima pra estação B
def bfs_01(origin):
  queue_0 = []
  queue_0_start, queue_0_end = 0, 0
  queue_1 = []
  for v in range(1, n + 1):
    dist[v] = INF

  dist[origin] = 1
  queue_0.append(origin)
  queue_0_end += 1
  
  while queue_0_start < queue_0_end:
    v = queue_0[queue_0_start]
    queue_0_start += 1

    for (w, d) in graph[v]:
      if dist[w] < INF:
        continue
      dist[w] = dist[v] + d
      if d == 0:
        queue_0.append(w)
        queue_0_end += 1
      else:
        queue_1.append(w)

    if queue_0_start == queue_0_end:
      # fila com a distancia atual ta vazia, vou pra proxima
      queue_0, queue_1 = queue_1, queue_0
      queue_0_start, queue_0_end = 0, len(queue_0)
      queue_1 = []

  return min(dist[vtx(0, B)], dist[vtx(1, B)])


mresp = bfs_01(vtx(0, A)) # começando no metro
oresp = bfs_01(vtx(1, A)) # começando no onibus
if mresp == INF and oresp == INF:
  print(-1)
else:
  print(min(mresp, oresp) * p)
