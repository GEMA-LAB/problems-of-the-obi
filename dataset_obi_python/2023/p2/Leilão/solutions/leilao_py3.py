#!/usr/bin/env python3

# OBI2023
# Tarefa Leilão
# r. anido

n = int(input())

melhor_valor = 0
melhor_name = ""

for i in range(n):
    nome = input()
    valor = int(input())
    if valor > melhor_valor:
        melhor_valor = valor
        melhor_nome = nome

print(melhor_nome)
print(melhor_valor)
