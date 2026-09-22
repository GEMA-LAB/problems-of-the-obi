#!/usr/bin/env python3

# OBI2021 - Fase 2
# Soma de dígitos

s = int(input())
a = int(input())
b = int(input())

resposta = 0

for i in range(a, b + 1):
    soma = 0
    num = i
    while num > 0:
        soma += num % 10
        num //= 10

    if soma == s:
        resposta += 1

print(resposta)


