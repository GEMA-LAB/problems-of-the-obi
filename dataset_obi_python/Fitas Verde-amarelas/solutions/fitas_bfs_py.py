#!/usr/bin/env python3

from collections import deque

dl = [-1, 0, 1, 0]
dc = [0, 1, 0, -1]

[n, m] = list(map(int, input().split()))
grid = []
comp = []
for i in range(n):
    grid.append(input())
    comp.append([0 for j in range(m)])
comp_atual = 0

# busca em largura
def bfs(orig_l, orig_c):
    global n, m, comp, grid, comp_atual
    q = deque()
    q.append((orig_l, orig_c))
    comp[orig_l][orig_c] = comp_atual
    while q:
        l, c = q.popleft()
        for i in range(4):
            nl, nc = l + dl[i], c + dc[i]
            if nl < 0 or nl >= n or nc < 0 or nc >= m:
                continue
            if grid[nl][nc] == '#' and comp[nl][nc] == 0:
                comp[nl][nc] = comp_atual
                q.append((nl, nc))

# encontra componentes conexas
for l in range(n):
    for c in range(m):
        if grid[l][c] == '#' and comp[l][c] == 0:
            comp_atual += 1
            bfs(l, c)

# testa colocar fitas horizontais em cada componente
fitas_hor = [0 for i in range(comp_atual + 1)]
for l in range(n):
    for c in range(m):
        if grid[l][c] != '#':
            continue
        if c == 0 or grid[l][c - 1] != '#':
            fitas_hor[comp[l][c]] += 1

# testa colocar fitas verticais em cada componente
fitas_ver = [0 for i in range(comp_atual + 1)]
for c in range(m):
    for l in range(n):
        if grid[l][c] != '#':
            continue
        if l == 0 or grid[l - 1][c] != '#':
            fitas_ver[comp[l][c]] += 1

# pega a melhor opcao pra cada componente
resp = 0
for i in range(1, comp_atual + 1):
    resp += min(fitas_hor[i], fitas_ver[i])

print(resp)
