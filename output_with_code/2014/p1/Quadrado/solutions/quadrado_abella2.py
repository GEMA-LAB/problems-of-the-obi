#!/usr/bin/env python2.7

n = int(raw_input())
A = [[int(value) for value in raw_input().split()] for y in xrange(n)]
correct = sorted([sum(A[0]), sum(A[1]), sum(A[2])])[1]

for y in xrange(n):
    if sum(A[y]) != correct:
        cy = y
for x in xrange(n):
    if sum([A[y][x] for y in xrange(n)]) != correct:
        cx = x

print A[cy][cx] + (correct - sum(A[cy])), A[cy][cx]
