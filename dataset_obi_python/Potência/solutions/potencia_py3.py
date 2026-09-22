#!/usr/bin/env python3

# OBI2021 - Fase 2
# Potencia

N = int(input())

resultado = 0

for i in range(N):
    T = int(input())

    pot = T % 10
    base = T // 10

    potencia = 1
    for j in range(pot):
        potencia *= base

    resultado += potencia

print(resultado)
