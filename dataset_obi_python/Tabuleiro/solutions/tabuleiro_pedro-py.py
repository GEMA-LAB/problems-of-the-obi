#!/usr/bin/env python3

M = 1_000_000_007

n = int(input())

a, b, c = 0, 0, 1

for i in range(n):
    x = c + 2 * (a + b)
    while x >= M:
        x -= M
    a = b
    b = c
    c = x

print(c)
