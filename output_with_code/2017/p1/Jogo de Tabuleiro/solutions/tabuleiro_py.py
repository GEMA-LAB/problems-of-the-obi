#!/usr/bin/env python2.7

N = int(raw_input())

tab = [[] for _ in range(N)]

for i in range(N):
    tab[i] = [int(v) for v in raw_input().split()]

for i in range(1,N):
    for j in range(1,N):
        if ( tab[i][j-1]+tab[i-1][j-1]+tab[i-1][j] > 1 ):
            tab[i][j] = 0
        else:
            tab[i][j] = 1

print tab[N-1][N-1]
