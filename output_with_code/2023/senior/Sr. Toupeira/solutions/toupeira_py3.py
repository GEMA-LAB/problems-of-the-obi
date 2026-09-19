#!/usr/bin/env python3

# OBI2023
# Tarefa Toupeira
# r. anido

s,t = [int(i) for i in input().split()]

# matriz de adjacências
adj = [[False for i in range(s)] for i in range(s)]

for i in range(t):
    i,j = [int(i) for i in input().split()]
    i -= 1
    j -= 1
    adj[i][j] = True
    adj[j][i] = True

p = int(input())

total = 0
for i in range(p):
    passeio = [int(i) for i in input().split()]
    ok = True
    corrente = passeio[1] - 1
    for k in passeio[2:]:
        if adj[corrente][k-1]:
            corrente = k-1
        else:
            ok = False
            break
    if ok:
        total += 1

print(total)

