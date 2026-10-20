#!/usr/bin/env python3

c = int(input())
d = int(input())
t = int(input())

litros = d / c

compra = litros - t

if compra < 0:
    compra = 0

print('{:.1f}'.format(compra))
