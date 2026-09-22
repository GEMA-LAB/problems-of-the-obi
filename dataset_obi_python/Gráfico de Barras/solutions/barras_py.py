#!/usr/bin/env python3

n = int(input())
v = list(map(int, input().split()))

maior = max(v)

matriz = [[0]*n for _ in range(maior)]

for i in range(n):
    for j in range(maior - v[i], maior):
        matriz[j][i] = 1

for linha in matriz:
    for num in linha:
        print(num, end = " ")
    print()
