#!/usr/bin/env python3
# solução para o problema "Jogo de par ou ímpar"

# lê a entrada
p = int(input())
d1 = int(input())
d2 = int(input())

# calcula e escreve o resultado
if (d1+d2) % 2 == p:        
    print(0)
else:
    print(1)


