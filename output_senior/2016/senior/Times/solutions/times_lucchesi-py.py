#!/usr/bin/env python
# coding: utf-8
# solução para o problema "times"

import sys

def enqueue(v, r):
    if  rotulo[v] == 2:
        rotulo[v] = r
        queue.append(v)
    
def bfs():
    while queue != []:
        v = queue.pop(0)
        r = 1 - rotulo[v]
        for w in adj[v]: enqueue(w, r)

queue = []
s = sys.stdin.readline().split()
n = int(s.pop(0))
adj = [[]]
rotulo = [2 for v in range(n+1)]

## print "n =", n

for v in range(1, n + 1):
    s = sys.stdin.readline().split()
    m = int(s.pop(0))
    adj.append([])
    for j in range(m):
        adj[v].append(int(s.pop(0)))

enqueue (1, 0)
bfs()

for r in range(2):
    sep = ""
    for v in range(1, n+1):
        if rotulo[v] == r:
            sys.stdout.write("%s%d" % (sep, v));
            sep = " "
    sys.stdout.write("\n")
