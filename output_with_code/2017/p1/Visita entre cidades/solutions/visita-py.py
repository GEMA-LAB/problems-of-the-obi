#!/usr/bin/env python2.7

# Guilherme A. Pinto, OBI-2017, visita

import sys

def dfs( atual, pai, dist, destino ):
    if ( atual == destino ):
        print dist
        return True

    for [c,d] in g[atual]:
        if ( c != pai ):
            if ( dfs( c, atual, dist + d, destino ) ):
                return True

    return False
            
[N, A, B] = [int(c) for c in raw_input().split()]

g = [[] for _ in range(N+1)]

for i in range(1,N):
    [P, Q, D] = [int(c) for c in raw_input().split()]
    g[P].append( [Q, D] )
    g[Q].append( [P, D] )

sys.setrecursionlimit(10**5)

dfs( A, -1, 0, B )
