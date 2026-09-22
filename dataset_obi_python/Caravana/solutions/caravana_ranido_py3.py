#!/usr/bin/env python3

n = int(input())

soma = 0
pesos = []
for i in range(n):
    p = int(input())
    soma += p
    pesos.append(p)

ideal = soma // n

for p in pesos:
    print(ideal - p)


