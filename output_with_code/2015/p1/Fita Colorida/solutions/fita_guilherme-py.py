#!/usr/bin/env python2.7

N = int(raw_input())

fita = [int(x) for x in raw_input().split()]
fita[N:] = [-1]  # insere um -1 no final
fita[:0] = [-1]  # insere um -1 no inicio

for c in xrange(8):
    for i in xrange(1,N+1):
        if ( fita[i] == -1 ):
            if ( fita[i-1] == c or fita[i+1] == c ):
                fita[i] = c + 1

for i in xrange(1,N+1):
    if ( fita[i] == -1 ):
        fita[i] = 9

for i in xrange(1,N):
    print fita[i],
print fita[N]

