#!/usr/bin/env python3
# OBI-2019, xadrez

[N,T] = [int(i) for i in input().split()]

res = 0

if T == 0:
    res = N
elif T == 1:
    res = N*(N-1) # combinação de N dois a dois, vezes dois (por quê?)
else:
    res = (N*(N-1)*(N-2))//6 # combinação de N três a três (por quê?)

print( res )
