#!/usr/bin/env python3

preco_total = 0

N = int(input())
for d in range(1, N+1):
    if(N % d == 0):
        c = N // d
        caixa_simples = (10 + 3 * d)
        caixa_enfeitada = (2 + c) * caixa_simples
        pedido = caixa_enfeitada * c
        preco_total += pedido

print(preco_total)
