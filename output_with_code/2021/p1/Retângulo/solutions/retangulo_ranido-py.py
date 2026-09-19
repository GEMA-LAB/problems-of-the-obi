#!/usr/bin/env python3

from sys import stdin, stdout

N = int(stdin.readline())

trees = [int(i) for i in stdin.readline().split()]

arc_sum = 0
for i in range(N):
    arc_sum = arc_sum - trees[i]

# apontadores
p,q = 0,0

# contador para o número de semi-circulos de mesmo comprimento
a = 0

# existe retângulo se há pelo menos dois pares de pontos diametralmente opostos
while q != N and a < 2:
    if arc_sum > 0:
        # advance p
        arc_sum = arc_sum - 2*trees[p]
        p += 1
    elif arc_sum < 0:
        # advance q
        arc_sum = arc_sum + 2*trees[q]
        q += 1
    else:
        # advance p and q
        arc_sum = arc_sum - 2*trees[p] + 2*trees[q]
        p += 1
        q += 1
        a += 1

if a >= 2:
    stdout.write('S\n')
else:
    stdout.write('N\n')
