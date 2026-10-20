#! /usr/bin/env python3

import heapq

MAX = 10 ** 5 + 10
INF = 10 ** 9 + 10
adj = {}


def add_node(node):
    if node not in adj:
        adj[node] = []


def add_edge(node1, node2, w):
    add_node(node1)
    adj[node1].append((node2, w))


n, m, k = map(int, input().split())
p = [int(x) for x in input().split()]
p = [0] + p
d = {}
for i in range(1, m + 1):
    [u, v, t] = [int(x) for x in input().split()]
    add_edge((u, t), (v, t), 0)
    add_edge((u, t), (u, k + 1), 0)
    add_edge((v, t), (v, k + 1), 0)
    add_edge((v, t), (u, t), 0)
    add_edge((u, k + 1), (u, t), p[t])
    add_edge((v, k + 1), (v, t), p[t])
a, b = map(int, input().split())

# Dijkstra
sa = (a, k + 1)
d[sa] = 0

q = [(0, sa)]
heapq.heapify(q)
s = set()
qtd =0

while q:
    dist, v = heapq.heappop(q)

    if d[v] < dist or v not in adj:
        continue

    for viz, price in adj[v]:
        dd = dist + price

        if (viz not in d) or (dd < d[viz]):
            heapq.heappush(q, (dd, viz))
            d[viz] = dd

sb = (b, k + 1)

print(d.get(sb,-1))
