#!/usr/bin/env python3


N = int(input())
S = int(input())
X = [0 for i in range(N)]
for i in range(N):
    X[i] = int(input())
prox_ind = [N for i in range(N)]
prox_val = [0 for i in range(S+1)]

lg = N.bit_length() - 1
tabela = [[0 for j in range(N)] for i in range(lg + 1)]
for i in range(N-1, -1, -1):
    if(prox_val[X[i]] != 0):
        prox_ind[i] = prox_val[X[i]]
    prox_val[X[i]] = i

for i in range(N):
    tabela[0][i] = prox_ind[i]
for i in range(1, lg + 1):
    for j in range(N - (1<<i) + 1):
        tabela[i][j] = min(tabela[i-1][j], tabela[i-1][j + (1<<(i-1))])
l = 1
r = N + 1
while(l < r - 1):
    m = (l+r) // 2
    achou = False
    lg = m.bit_length() - 1
    sz = (1<<lg)
    for i in range(N - m + 1):
        minimo = min(tabela[lg][i], tabela[lg][i + m - sz])
        if(minimo >= i + m):
            achou = True
    if(achou):
        l = m
    else:
        r = m

print(l)