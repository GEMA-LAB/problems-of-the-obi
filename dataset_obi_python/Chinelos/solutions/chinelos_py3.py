#!/usr/bin/env python

# OBI2023                                                                                                                                          
# Tarefa                                                                                                                                   
# r. anido

n = int(input())

# vamos armazenar o estoque em um vetor
estoque = []

# ler valores do estoque
for i in range(n):
    x = int(input())
    estoque.append(x)

# número de pedidos
p = int(input())

# processa pedidos
total = 0
for k in range(p):
    i = int(input())
    if estoque[i-1] > 0:
        # tem estoque, atende pedido, atualiza estoque
        estoque[i-1] -= 1
        total += 1

# imprime resultado
print(total)
