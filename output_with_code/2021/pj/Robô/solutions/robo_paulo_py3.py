#!/usr/bin/env python3

N, C, P = map(int, input().split())
commands = list(map(int, input().split()))

pos, res = 1, 0

for cmd in commands:
    if pos == P:
        res += 1

    pos += cmd

    if pos == 0:
        pos = N
    elif pos > N:
        pos = 1

if pos == P:
    res += 1

print(res)
