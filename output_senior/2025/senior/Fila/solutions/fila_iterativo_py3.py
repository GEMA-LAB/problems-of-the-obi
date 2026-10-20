#!/usr/bin/env python3
from collections import deque
preco_total = 0

N, M = [int(x) for x in input().split()]
P = [int(x) for x in input().split()]

vert_map = [-1] * N
ult = 0
V = 0
for i in range(N):
    if(P[i] > ult): # abre
        V += 1
        vert_map[i] = V
    ult = P[i]

V += 1
pai = [-1 for i in range(V)]
grau = [0 for i in range(V)]
freq = [dict() for i in range(V)]
pilha = [-1]
for i in range(N):
    if(vert_map[i] != -1):
        pilha.append(i)
    else:
        a = pilha[-1]
        pilha.pop()
        b = i
        v = vert_map[a]
        p = pilha[-1]
        p = 0 if (p == -1) else vert_map[p]
        freq[v] = {P[a] : 1, P[b] : 1}
        pai[v] = p
        grau[p] += 1

ans = [[-1,-1]] * V
most_freq = [[-1,-1] for i in range(V)]
large_freq =[freq[i] for i in range(V)]

def mergear_no_pai(b):
    a = pai[b]
    if(a == -1):
        return

    if(most_freq[b][1] > most_freq[a][1]):
        most_freq[a] = [most_freq[b][0], most_freq[b][1]]
    elif(most_freq[b][1] == most_freq[a][1] and most_freq[b][0] < most_freq[a][0]):
        most_freq[a] = [most_freq[b][0], most_freq[b][1]]
    if(len(large_freq[b]) > len(large_freq[a])):
        large_freq[b], large_freq[a] = large_freq[a], large_freq[b]
    for key, value in large_freq[b].items():
        if(not(key in large_freq[a])):
            large_freq[a][key] = 0
        large_freq[a][key] += value
        if(large_freq[a][key] > most_freq[a][1]):
            most_freq[a] = [key, large_freq[a][key]]
        elif(large_freq[a][key] == most_freq[a][1] and key < most_freq[a][0]):
            most_freq[a] = [key, large_freq[a][key]]

def resolve():
    q = deque()
    for i in range(V):
        for key, value in large_freq[i].items():
            if(value > most_freq[i][1]):
                most_freq[i] = [key, value]
            elif(value == most_freq[i][1] and key < most_freq[i][0]):
                most_freq[i] = [key, value]
        if(grau[i] == 0):
            q.append(i)

    while(len(q) > 0):
        b = q.popleft()
        ans[b] = [most_freq[b][0], most_freq[b][1]]
        mergear_no_pai(b)
        most_freq[b].clear()
        large_freq[b].clear()
        if(pai[b] != -1):
            grau[pai[b]] -= 1
            if(grau[pai[b]] == 0):
                q.append(pai[b])

resolve()

for i in range(M):
    c, t = [int(x) for x in input().split()]
    c -= 1
    t -= 1
    v = vert_map[c]
    print(f"{ans[v][0]} {ans[v][1]}")