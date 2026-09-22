#!/usr/bin/env python3

N = int(input())
A = list(map(int, input().split()))

INF = 10**15
left = [INF] * N
right = [INF] * N

# Passagem esquerda -> direita
last_val, last_pos = -INF, -INF
for i in range(N):
    if A[i] != -1:
        last_val, last_pos = A[i], i
    if last_val != -INF:
        left[i] = last_val + (i - last_pos)

# Passagem direita -> esquerda
last_val, last_pos = -INF, -INF
for i in range(N - 1, -1, -1):
    if A[i] != -1:
        last_val, last_pos = A[i], i
    if last_val != -INF:
        right[i] = last_val + (last_pos - i)

# Combina os dois lados
ans = [min(left[i], right[i]) for i in range(N)]

for i in range(N):
    print(ans[i],end=' ')

