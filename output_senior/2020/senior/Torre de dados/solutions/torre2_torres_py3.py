#!/usr/bin/env pypy3
# torre de dados
# obi2020 - fase 3

from itertools import permutations

def max_lado(n, top):
    bottom = lado[top];
    max=0;
    for i in range(6):
        if i == top or i == bottom:
            continue
        if max < dado[n][i]:
            max = dado[n][i]
    return max


def encontra(n, value):
    for i in range(6):
        if dado[n][i] == value:
            return i
    return -1


lado = (5, 3, 4, 1, 2, 0)
dado = []

# le entrada
n = int(input())

for i in range(n):
    tmp = input().split()
    um_dado = [int(j) for j in tmp]
    dado.append(um_dado)
  
# processa
resultado = 0

for ordem in permutations(range(n),n):
    for primeiro in range(6):
        base_anterior = dado[ordem[0]][lado[primeiro]]
        soma = max_lado(ordem[0], primeiro);
        for k in range(1,n):
            i = ordem[k]
            topo_corrente = encontra(i,base_anterior);
            soma += max_lado(i,topo_corrente);
            base_anterior = dado[i][lado[topo_corrente]];
        if soma > resultado:
            resultado = soma
    
# escreve resultado
print(resultado);
