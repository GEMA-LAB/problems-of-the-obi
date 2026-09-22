#!/usr/bin/env python3

# OBI2021
# Fase 3
# Sr. Sapo

def bfs(ini, dest):
    global lago, N, M
    visitado = [[False for i in range(M+1)] for j in range(N+1)]
    fila = [ini]
    while len(fila) > 0:
        col,lin = fila.pop(0)
        if col == dest[0] and lin == dest[1]:
            return('S')
        if not visitado[col][lin]:
            visitado[col][lin] = True
            for passo in (1,2,3):
                if col + passo <= N and lago[col+passo][lin]:
                    fila.append((col+passo,lin))
                if col - passo >= 0 and lago[col-passo][lin]:
                    fila.append((col-passo,lin))
                if lin + passo <= M and lago[col][lin+passo]:
                    fila.append((col,lin+passo))
                if lin - passo >= 0 and lago[col][lin-passo]:
                    fila.append((col,lin-passo))
    return 'N'

N,M = [int(i) for i in input().split()] 
P = int(input())
lago = [[False for i in range(M+1)] for j in range(N+1)]
for i in range(P):
    col,lin = [int(k) for k in input().split()]
    lago[col][lin] = True

Ci,Li = [int(i) for i in input().split()]
Cd,Ld = [int(i) for i in input().split()]

print(bfs((Ci,Li),(Cd,Ld)))
