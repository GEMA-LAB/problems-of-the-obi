#!/usr/bin/env python3

# union-find

pai = []
tam = []

[n, m, k] = list(map(int, input().split()))
edges = []
for i in range(m):
  [a, b, t] = list(map(int, input().split()))
  edges.append((t, a, b))


def init(n):
    global pai, tam
    pai = list(range(n))
    tam = [1 for i in range(n)]

def find(a):
    global pai
    while pai[a] != a:
        pai[a] = pai[pai[a]]
        a = pai[a]
    return a

def union(a, b):
    global pai, tam
    a = find(a)
    b = find(b)
    if a == b:
        return False
    if tam[a] < tam[b]:
        a, b = b, a
    pai[b] = a
    tam[a] += tam[b]
    return True

def same(a, b):
    return find(a) == find(b)


init(n + 1)
edges.sort()

min_removals = 0
hydro_cycle = False

for edge in edges:
  t, a, b = edge
  ret = union(a, b)
  if not ret:
    if t == 1:
      hydro_cycle = True
    else:
      min_removals += 1

if hydro_cycle or min_removals > k:
  print("N")
else:
  print("S")

