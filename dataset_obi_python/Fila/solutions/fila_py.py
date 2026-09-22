#!/usr/bin/env python3

#   OBI 2025 - Fase 1
#   Dieta


n = int(input())
v = list(map(int, input().split()))

maior = -1
nao_visiveis = 0
for i in range(n - 1, -1, -1):
    if v[i] <= maior:
        nao_visiveis += 1
    maior = max( maior, v[i] )
print(nao_visiveis)