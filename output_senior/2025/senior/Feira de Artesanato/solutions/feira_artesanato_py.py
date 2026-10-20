#!/usr/bin/env python3

remover_lazy = dict()
remover_lazy_vetor = []
produtos = []
todos_produtos = []
n, tam = map(int, input().split())
tt = list(map(int, input().split()))
pp = list(map(int, input().split()))

def remover(t, p):
    global remover_lazy
    remover_lazy[(p, t)]+= 1
    remover_lazy_vetor[t][p] += 1    

for i in range(tam+1):
    produtos.append([])
    remover_lazy_vetor.append(dict())

for i in range(n):
    produtos[tt[i]].append(pp[i])
    todos_produtos.append((pp[i], tt[i]))
    remover_lazy[(pp[i], tt[i])] = 0
    remover_lazy_vetor[tt[i]][pp[i]] = 0

for i in range(1, tam+1):
    produtos[i].sort(reverse = True)

todos_produtos.sort(reverse = True)

c = int(input())
cc = list(map(int, input().split()))
res = 0
for i in range(c):
    t = cc[i]
    if t == 0:
        while len(todos_produtos) > 0:
            p = todos_produtos[-1]
            if remover_lazy[p] > 0:
                remover_lazy[p] -= 1
                todos_produtos.pop()
            else: 
                break
        if len(todos_produtos) == 0:
            continue
        p = todos_produtos[-1]
        remover(p[1], p[0])
        res += p[0]
    else:
        while len(produtos[t]) > 0:
            p = produtos[t][-1]
            if remover_lazy_vetor[t][p] > 0:
                remover_lazy_vetor[t][p] -= 1
                produtos[t].pop()
            else:
                break
        if len(produtos[t]) == 0:
            continue
        p = produtos[t][-1]
        aux = (p, t)
        remover(t, p)
        res += p
print(res)


