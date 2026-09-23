#!/usr/bin/env python2.7

[N, M] = [int(c) for c in raw_input().split()]

g = [[] for _ in range(N+1)]
marca = [0 for _ in range(N+1)]
cor = [0 for _ in range(N+1)]

def dfs( a ):
    if ( marca[a] == count ): return False
    marca[a] = count
    if ( a == Q ):
        cor[a] = C
        return True
    for v in g[a]:
        if ( dfs( v ) ):
            cor[a] = C
            return True
    return False

for i in range(N-1):
    [U, V] = [int(c) for c in raw_input().split()]
    g[U].append( V )
    g[V].append( U )
    
for count in range(1,M+1):
    [P, Q, C] = [int(c) for c in raw_input().split()]
    dfs( P )
    
for i in range(1,N+1):
    print cor[i],
print
