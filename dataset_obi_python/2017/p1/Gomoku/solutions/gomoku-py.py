#!/usr/bin/env python3
import sys
# Solucao para o problema Gomoku
# Ricardo Anido

N=15

#vamos usar a tupla direcao para facilitar percorrer a matriz
direcao=(
  (0,1),
  (1,0),
  (1,1),
  (1,-1));

# vamos usar um tabuleiro com "bordas", ou seja, um
# tabuleiro rodeado por valores zero, para nao ter
# que testar se sairmos fora do tabuleiro enquanto 
# percorremos
tabuleiro=[[0 for i in range(N+2)]] # a primeira linha tem apenas zeros
# le a entrada
for i in range(N):
    linha=[int(i) for i in input().split()]
    tabuleiro.append([0]+linha+[0])  # cada linha inicia e termina com zero

tabuleiro.append([0 for i in range(N+2)]) # a ultima linha tem apenas zeros

# procura cinco pedras de mesma cor nas quatro direcoes
res,cor=0,0
for dir in direcao:
    for y in range(1,N+2):
        for x in range(1,N+2):
            cor=tabuleiro[y][x]
            if cor==0:
                continue
            if tabuleiro[y][x] != tabuleiro[y-dir[0]][x-dir[1]]:
                conta=0
                yh,xh=y,x
                while(tabuleiro[yh][xh]==cor):
                    yh+=dir[0]
                    xh+=dir[1]
                    conta+=1
                if conta==5:
                    res=cor

print(res)
