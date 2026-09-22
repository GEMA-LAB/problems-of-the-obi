#!/usr/bin/env python3

from queue import Queue

N, M, K = input().split(' ')
N, M, K = int(N), int(M), int(K)

g = [[] for _ in range(N)]
apoio = [0] * N
quebrado = [False] * N
retirado = [False] * N
tentar_retirar = [False] * N

for _ in range(M):
    a, b = input().split(' ')
    a, b = int(a) - 1, int(b) - 1
    g[a].append(b)
    apoio[b] += 1


r = input().split(' ')
for i in range(K):
    r[i] = int(r[i]) - 1
    tentar_retirar[r[i]] = True

for _r in range(K):
    i = r[_r]
    if tentar_retirar[i] and not quebrado[i]:
        retirado[i] = True
        q = Queue()
        q.put(i)
        while not q.empty():
            v = q.get()
            for u in g[v]:
                apoio[u] -= 1
                if apoio[u] == 0 and not quebrado[u] and not retirado[u]:
                    quebrado[u] = True
                    q.put(u)

resposta = sum(1 for x in quebrado if x)
print(resposta)

