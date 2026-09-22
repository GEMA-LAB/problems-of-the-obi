#!/usr/bin/env python3

# OBI2023                                                                                                                                          
# Tarefa                                                                                                                                   
# r. anido

valor = int(input())
acougue = int(input())
farmacia = int(input())
padaria = int(input())

# armazena valores num vetor, para usar função de ordenação
contas = sorted([acougue, farmacia, padaria])

# com os valores ordenados podemos decidir quantas
#  contas podem ser pagas
if contas[0] + contas[1] + contas[2] <= valor:
    resp = 3
elif contas[0] + contas[1] <= valor:
    resp = 2
elif contas[0] <= valor:
    resp = 1
else:
    resp = 0

# imprime resposta
print(resp)
