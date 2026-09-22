#!/usr/bin/env python3

# R. Anido
# Sequência secreta - OBI2019

n = int(input())

atual = -1 # um número diferente dos valores 1 e 2
total = 0  # total de números marcados

for i in range(n):
    x = int(input())
    # cada vez que encontra um número diferente do 
    # último marcado, marca esse novo número
    if atual != x:
        atual = x
        total += 1

print(total)
