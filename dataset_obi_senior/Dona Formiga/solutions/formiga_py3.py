#!/usr/bin/env python3

# OBI2020
# dona formiga


def busca(k):
    if distancia[k] == -1:
        distancia[k] = 0
        for q in adj[k]:
            distancia[k] = max(distancia[k], busca(q) + 1)
    return(distancia[k])

S, T, P = [int(i) for i in input().split()]
altura = [int(i) for i in input().split()]
distancia = [-1 for i in range(S+1)]

adj = [[] for i in range(S)]

for i in range(T):
    a,b = [int(i) for i in input().split()]
    a -= 1
    b -= 1
    if altura[a] > altura[b]:
        adj[a].append(b)
    elif altura[a] < altura[b]:
        adj[b].append(a)

print(busca(P-1))
