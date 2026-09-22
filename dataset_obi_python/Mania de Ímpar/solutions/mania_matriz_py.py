#!/usr/bin/env python3

#   OBI 2025 - Fase 2
#   Matriz

n, m = map(int, input().split())

mat = [[0]*m for i in range(n)]
resp = [0]*2

for i in range(n):
    mat[i] = list(map(int, input().split()))
    for j in range(m):
        resp[(i + j + mat[i][j])%2] += 1

print(min(resp[0], resp[1]))

opt = 0 if resp[0] < resp[1] else 1

for i in range(n):
    for j in range(m):
        if (i + j + mat[i][j])%2 == opt:
            mat[i][j] += 1
        print(mat[i][j], end = " ")
    print()
