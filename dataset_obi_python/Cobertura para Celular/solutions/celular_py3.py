#!/usr/bin/env pypy3
import sys
sys.setrecursionlimit(5000)

# celular                                                                                                                                                                            
# obi2020 fase 3                                                                                                                                                                       

def sq(x):
    return x*x

MAX = 10010;

def dfs(idx):
    if marcado[idx]:
        return
    marcado[idx] = 1
    for i in range(len(adj[idx])):
        dfs(adj[idx][i]);
        
# le entrada
N = int(input())

X = [0 for i in range(N)]
Y = [0 for i in range(N)]

for i in range(N):
    X[i],Y[i] = [int(k) for k in input().split()]

A = int(input())
A *= A;

adj = [[] for i in range(N)]
marcado = [0 for i in range(N)]

for i in range(N):
    for j in range(i+1,N):
        if sq(X[i]-X[j]) +sq(Y[i]-Y[j]) <= A:
            adj[i].append(j)
            adj[j].append(i)
            
# verifica se conexo
dfs(0)
ok = True;
for i in range(N):
    ok &= marcado[i]
    if not ok:
        break

if ok:
    print("S");
else:
   print("N");
