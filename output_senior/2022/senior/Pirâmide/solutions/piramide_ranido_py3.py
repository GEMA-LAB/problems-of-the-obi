#!/usr/bin/env python3

# OBI2022 - Fase 2
# problema piramide
# r. anido

n = int(input())

# monta plano com zeros
# poderia montar com uns, para economizar!

plano = [[0 for i in range(n)] for i in range(n)]


def camada(k, n):
    # 1 <= k <= n
    # linha superior
    for i in range(k-1, n-k+1):
        plano[k-1][i] = k

    # linha inferior
    for i in range(k-1, n-k+1):
        plano[n-k][i] = k        

    # coluna esquerda
    for j in range(k-1, n-k+1):
        plano[j][k-1] = k        
        
    # coluna direita
    for j in range(k-1, n-k+1):
        plano[j][n-k] = k        
    

for i in range(1,2+n//2):
    camada(i,n)
    
# imprime o plano
for i in range(n):
    for j in range(n-1):
        print(plano[i][j], end = ' ') 
    print(plano[i][n-1])   # último valor da linha
    
