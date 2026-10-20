#!/usr/bin/env python3

from collections import deque

[n, m, k] = list(map(int, input().split()))

adj = [[] for i in range(n + 1)]
comp = [[0 for i in range(n + 1)] for g in range(2)]
cur_comp = [0, 0]
hydro_cycle = False
cnt_rod = 0

for i in range(m):
  [a, b, t] = list(map(int, input().split()))
  adj[a].append((b, t))
  adj[b].append((a, t))
  if t == 2:
    cnt_rod += 1


# busca em largura
def bfs(g, orig_v):
  global comp, cur_comp, hydro_cycle

  q = deque()
  q.append((orig_v, orig_v))
  comp[g][orig_v] = cur_comp[g]

  while q:
    v, p = q.popleft()
    for w, t in adj[v]:
      if g == 0 and t == 2:
        continue
      if w == p:
        continue
      if comp[g][w]:
        if g == 0:
          hydro_cycle = True
        continue
      comp[g][w] = cur_comp[g]
      q.append((w, v))


for g in range(2):
  for v in range(1, n + 1):
    if not comp[g][v]:
      cur_comp[g] += 1
      bfs(g, v)

if hydro_cycle:
  print("N")
  exit(0)

allowed_edges = cur_comp[0] - cur_comp[1]
forbidden_edges = cnt_rod - allowed_edges

if forbidden_edges > k:
  print("N")
else:
  print("S")

