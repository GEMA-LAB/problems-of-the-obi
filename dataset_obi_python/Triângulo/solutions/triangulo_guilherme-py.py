#!/usr/bin/env python2.7
# encoding: utf-8

# Guilherme A. Pinto - OBI 2014 - Triangulo

import sys

def get_linha_num(dados):
    for i in range(len(dados)):
        dados[i] = int(dados[i])
    return dados

def triangulo( p, q, r ):
    if ( p < q+r and q < p+r and r < p+q ): return True
    return False

finput = sys.stdin
linha = finput.readline()[:-1]

a,b,c,d = get_linha_num(linha.split(" "))

if ( triangulo( a, b, c ) or
     triangulo( a, b, d ) or
     triangulo( a, c, d ) or
     triangulo( b, c, d ) ):
    print "S"
else:
    print "N"

sys.exit(0)
