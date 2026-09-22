#!/usr/bin/env python2.7

# Guilherme A. Pinto, OBI-2017, zip

def pontuacao( a, b ):
    p = a + b
    if ( a == b ):
        p *= 2
    if ( abs(a-b) == 1 ):
        p *= 3
    return p

[l1] = [int(c) for c in raw_input().split()]
[l2] = [int(c) for c in raw_input().split()]
[c1] = [int(c) for c in raw_input().split()]
[c2] = [int(c) for c in raw_input().split()]

pLia = pontuacao( l1, l2 )
pCarolina = pontuacao( c1, c2 )

if ( pLia == pCarolina ):
    print "empate"
elif ( pLia > pCarolina ):
    print "Lia"
else:
    print "Carolina"
