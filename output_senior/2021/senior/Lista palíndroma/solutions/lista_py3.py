#!/usr/bin/env python3

# OBI2021 - Fase 2
# Lista palíndroma


n = int(input())
lista = [int(k) for k in input().split()]

sol = 0
p_esq = 0    # apontador para o elemento à esquerda
p_dir = n - 1 # apontador para o elemento à direita

while (p_esq < p_dir):
    if lista[p_esq] == lista[p_dir]:
        p_esq += 1
        p_dir -= 1
        continue

    if lista[p_esq] < lista[p_dir]:
        lista[p_esq + 1] += lista[p_esq]
        p_esq += 1
    else:
      lista[p_dir - 1] += lista[p_dir]
      p_dir -= 1

    sol += 1

print(sol)
