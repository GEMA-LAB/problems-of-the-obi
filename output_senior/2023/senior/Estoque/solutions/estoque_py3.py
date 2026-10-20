#!/usr/bin/env python3

m,n = [int(x) for x in input().split()]

estoque = []
for i in range(m):
    linha = [int(x) for x in input().split()]
    estoque.append(linha)

p = int(input())

total = 0
for k in range(p):
    i, j = [int(x) for x in input().split()]
    if estoque[i-1][j-1] > 0:
        estoque[i-1][j-1] -= 1
        total += 1

print(total)
