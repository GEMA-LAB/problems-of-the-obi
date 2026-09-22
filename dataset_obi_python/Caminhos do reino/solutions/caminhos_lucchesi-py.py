#!/usr/bin/env python
# coding: utf-8
# solução para o problema "reino"

import sys

##
## in_d[v] = in_degree[v]
##
## d2cycle[v] = distance from v to nearest vertex in cycle (0 if v in
## cycle) 
##
## or_cycle = a vertex in the cycle
##
## d_from_or_cycle[v] = distance from or_cycle to v, if v in cycle
##
## len_cycle = number of vertices in the cycle
##
## end_per[v] = end of peripheral path containing v (v itself if v in
## cycle)
##

def dfs(v):
    stack = [v]
    while d2cycle[v] != 0:
        stack.append(f[v])
        v = f[v]
    ell = 0
    e_per = v
    while stack != []:
        v = stack.pop()
        d2cycle[v] = ell
        ell += 1
        end_per[v] = e_per

n = int(sys.stdin.readline().split().pop(0))

in_d = [0 for v in range(n+1)]
d2cycle = [n for v in range(n+1)]
d_from_or_cycle = [0 for v in range(n+1)]
end_per = [0 for v in range(n+1)]

f = [0] ## dummy

## lê input e calcula in_d
s = sys.stdin.readline().split()
for v in range(1, n+1):
    f.append(int(s.pop(0)))
    in_d[f[v]] += 1

## find cycle
for v in range(1, n+1):
    if in_d[v] > 1:
        or_cycle = v
        break
    
len_cycle = 0
v = or_cycle
while(True):
    d2cycle[v] = 0
    d_from_or_cycle[v] = len_cycle
    len_cycle += 1
    end_per[v] = v
    v = f[v]
    if v == or_cycle: break

## peripheral paths: end of peripheral path and distance to cycle
for v in range(1, n+1):
    if in_d[v] == 0: dfs(v)

q = int(sys.stdin.readline().split().pop(0))
for i in range(q):
    s = sys.stdin.readline().split()
    v = int(s.pop(0))
    w = int(s.pop(0))
    if d2cycle[v] < d2cycle[w]: v, w = w, v
    if end_per[v] == end_per[w]: res = d2cycle[v] - d2cycle[w]
    else:
        d_end_v2end_w = d_from_or_cycle[end_per[w]] - d_from_or_cycle[end_per[v]]
        if d_end_v2end_w < 0: d_end_v2end_w += len_cycle
        res = min(d2cycle[v] + d_end_v2end_w, max(d2cycle[v], d2cycle[w] + len_cycle - d_end_v2end_w))
    print res

