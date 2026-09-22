#!/usr/bin/env python2.7

# Guilherme A. Pinto, OBI-2017, onibus

import sys

def dfs( atual, pai, dist, destino ):
    if ( atual == destino ):
        print dist
        return True

    for p in g[atual]:
        if ( p != pai ):
            if ( dfs( p, atual, dist + 1, destino ) ):
                return True

    return False
            
[N, A, B] = [int(c) for c in raw_input().split()]

g = [[] for _ in range(N+1)]

for i in range(1,N):
    [P, Q] = [int(c) for c in raw_input().split()]
    g[P].append( Q )
    g[Q].append( P )

sys.setrecursionlimit(10**5)

dfs( A, -1, 0, B )
