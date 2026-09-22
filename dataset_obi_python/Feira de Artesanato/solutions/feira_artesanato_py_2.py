#!/usr/bin/env python3

import heapq

[n, sz] = list(map(int, input().split()))
t = list(map(int, input().split()))
p = list(map(int, input().split()))
[c] = list(map(int, input().split()))
u = list(map(int, input().split()))

freq_dict = {}

todos_pq = []
heapq.heapify(todos_pq)

tipo_pq = [[] for i in range(sz + 1)]
for i in range(sz + 1):
  heapq.heapify(tipo_pq[i])


for i in range(n):
  obj_atual = (p[i], t[i])

  if obj_atual not in freq_dict:
    freq_dict[obj_atual] = 0
  freq_dict[obj_atual] += 1

  heapq.heappush(todos_pq, obj_atual)
  heapq.heappush(tipo_pq[t[i]], obj_atual)


resp = 0

for tipo in u:

  if tipo == 0:
    best = None
    while len(todos_pq) > 0 and best not in freq_dict:
      best = heapq.heappop(todos_pq)
    if best not in freq_dict:
      continue

  else:
    best = None
    while len(tipo_pq[tipo]) > 0 and best not in freq_dict:
      best = heapq.heappop(tipo_pq[tipo])
    if best not in freq_dict:
      continue

  freq_dict[best] -= 1
  if freq_dict[best] == 0:
    del freq_dict[best]

  resp += best[0]

print(resp)

