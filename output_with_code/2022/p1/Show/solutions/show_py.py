#!/usr/bin/env python3

a,n,m = [int(i) for i in input().split()]

melhor_fila = n+1
for fila in range(n,0,-1):
    assentos =  [int(i) for i in input().split()]
    contiguos = 0
    for assento in assentos:
        if assento == 0:
            contiguos += 1
            if contiguos >= a:
                # amigos cabem nesta fila
                if fila < melhor_fila:
                    melhor_fila = fila
                break
        else:
            contiguos = 0

if melhor_fila == n+1:
    print(-1)
else:
    print(melhor_fila)
