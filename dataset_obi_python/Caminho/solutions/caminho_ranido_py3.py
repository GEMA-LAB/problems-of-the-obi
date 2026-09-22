#!/usr/bin/env python3

# OBI2022
# Fase 2
# caminhos

n = int(input())
postes = []
for i in range(n):
    postes.append(int(input()))

# adiciona cópias dos postes para considerar circularidade
for i in range(n):
    postes.append(postes[i])

max_tamanho = 0
tamanho = 0
for i in range(2*n-1):
    if postes[i] + postes[i+1] < 1000:
        tamanho += 1
        if tamanho > max_tamanho:
            max_tamanho = tamanho
    else:
        tamanho = 0

if max_tamanho>n:
    max_tamanho = n
    
print(max_tamanho)
