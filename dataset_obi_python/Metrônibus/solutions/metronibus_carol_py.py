#! /usr/bin/env python3

MAX = 10 ** 5 + 10


class Fila_dupla:
    def __init__(self):
        self.fila = [0] * (6 * MAX)
        self.ini = MAX * 3
        self.fim = MAX * 3

    def adiciona_atras(self, valor):
        self.fila[self.fim] = valor
        self.fim += 1

    def adiciona_frente(self, valor):
        self.ini -= 1
        self.fila[self.ini] = valor

    def popa(self):
        ret = self.fila[self.ini]
        self.ini += 1
        return ret

    def ta_vazia(self):
        return self.ini == self.fim


class Graph:
    def __init__(self, qtd_vertices):
        self.adj = {i: [] for i in range(qtd_vertices)}

    def add_aresta(self, no1, no2, peso):
        self.adj[no1].append((no2, peso))
        self.adj[no2].append((no1, peso))

    def vizinhos(self, no):
        return self.adj[no]


[n, k1, k2, p] = [int(x) for x in input().split()]
g = Graph(2 * n + 10)

for i in range(2):
    for j in range([k1, k2][i]):
        [u, v] = [int(x) for x in input().split()]
        u -= 1
        v -= 1
        g.add_aresta(u * 2 + i, v * 2 + i, 0)

[a, b] = [int(x) for x in input().split()]
a -= 1
b -= 1

for i in range(0, n):
    g.add_aresta(i * 2, i * 2 + 1, 1)

d = [MAX] * (2 * n + 10)

q = Fila_dupla()
q.adiciona_atras((0, a * 2))
q.adiciona_atras((0, a * 2 + 1))
d[a * 2] = 0
d[a * 2 + 1] = 0

while not q.ta_vazia():
    dist, vert = q.popa()

    if dist != d[vert]:
        continue

    for viz, peso in g.vizinhos(vert):
        if peso == 0 and d[viz] > dist:
            q.adiciona_frente((dist, viz))
            d[viz] = dist
        elif peso == 1 and (d[viz] > dist + 1):
            d[viz] = dist + 1
            q.adiciona_atras((d[viz], viz))

min_troca = min([d[b * 2], d[b * 2 + 1]]) + 1

if min_troca >= MAX:
    print(-1)

else:
    print(min_troca * p)
