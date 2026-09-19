#!/usr/bin/env python3

N = int(input())
S = int(input())
peguei = [False for i in range(S+1)]
X = []
for i in range(N):
    x = int(input())
    X.append(x)
resposta = 0
l = 0
atual = 0
for r in range(N):
    while(peguei[X[r]]):
        peguei[X[l]] = False
        atual -= 1
        l += 1
    peguei[X[r]] = True
    atual += 1
    resposta = max(resposta, atual)  
print(resposta)