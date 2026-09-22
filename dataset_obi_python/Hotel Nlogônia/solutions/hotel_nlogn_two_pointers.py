#!/usr/bin/env python3

"""
OBI 2024 - Fase 3
  Hotel Nlogônia
  Solução em O(N log N) com Two Pointers + Heap (ou "Sliding Window")
"""

import heapq

[n, d, w] = list(map(int, input().split()))

p = [0] + list(map(int, input().split()))

# somas parciais:
# psum guarda somas de prefixo;
# dsum guarda somas de intervalos de tamanho D
psum = [0 for _ in range(n + 1)]
dsum = [0 for _ in range(n + 1)]
for i in range(1, n + 1):
  psum[i] = psum[i - 1] + p[i]
  if i >= d:
    dsum[i] = psum[i] - psum[i - d]

# técnica de two pointers para encontrar o maior intervalo válido
resp = d
cur_tot = psum[d - 1]
l = 1

# Vamos guardar todas as somas para intervalos de tamanho D na
# janela atual do two pointers, ordenados decrescente por soma,
# em um heap para inserção/consulta do maior em O(log N)
dsums = []
heapq.heapify(dsums)

for r in range(d, n + 1):
  # adiciona r na janela do two pointers
  cur_tot += p[r]
  # [guarda -dsum[r] no no heap para ordenar decrescente;
  #  guarda também o índice de início para saber quando
  #  uma soma já não é mais válida (pois o início saiu da janela)]
  heapq.heappush(dsums, (-dsum[r], r - d + 1))

  # remove do heap os elementos no topo cujos inícios já saíram da janela
  while dsums[0][1] < l:
    heapq.heappop(dsums)
  
  # enquanto o custo estiver muito alto, remove l da janela do two pointers
  while r - l + 1 > d and cur_tot + dsums[0][0] > w:
    cur_tot -= p[l]
    l += 1
    while dsums[0][1] < l:
      heapq.heappop(dsums)

  resp = max(resp, r - l + 1)

print(resp)
