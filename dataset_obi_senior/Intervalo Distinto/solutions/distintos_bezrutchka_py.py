#! /usr/bin/env python3

# OBI 2023 - Fase 2
# Distintos - Solução O(N) gulosa usando dois ponteiros
# Mateus Bezrutchka

MAXVAL = 100001

n = int(input())
array = [int(input()) for i in range(n)]

ultimo_id = [-1 for i in range(MAXVAL)]
resp = 0

# para o fim atual, inicio guarda o menor índice
# tal que [inicio, fim] nao tem repetições
inicio = 0
for fim in range(0, n):
  x = array[fim]
  if ultimo_id[x] >= inicio:
    inicio = ultimo_id[x] + 1
  resp = max(resp, fim - inicio + 1)
  ultimo_id[x] = fim

print(resp)
