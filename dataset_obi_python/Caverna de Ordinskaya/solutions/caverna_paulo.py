#!/usr/bin/env python2.7
# encoding: utf-8

import sys

N, M = map(int, raw_input().split())

A = [int(value) for value in raw_input().split()]


prev = -1
res = 0

for i in range(N):
    mn = A[i]
    mx = M - A[i]
    if (mn > mx):
        mn, mx = mx, mn

    if (mn >= prev):
        A[i] = mn
    elif (mx >= prev):
        A[i] = mx
    else:
        print "-1"
        sys.exit(0)

    prev = A[i]
    res += prev

print res
