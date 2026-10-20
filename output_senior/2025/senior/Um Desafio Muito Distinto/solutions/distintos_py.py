#!/usr/bin/env python3



#   OBI 2025 - Fase 2
#   Distintos

from math import ceil

def sum( a : int, b : int ):
  return ((a + b)*(b - a + 1))//2


q = int(input())
for i in range(q):
    l, a, b = map(int, input().split())

    if a > l or a == b:
        print(1)
        continue
    if sum(a, b - 1) < l:
        print(b - a + 1)
        continue

    maxi = (-1 + (4*a**2 - 4*a + 8*l + 1)**0.5)/2
    val = int(ceil(maxi))
    print(val - a + 1)

