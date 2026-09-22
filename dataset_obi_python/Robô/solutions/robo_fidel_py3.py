#!/usr/bin/env python3
(N, C, S) = map(int, input().split())

RES = 0; cur = 1
for X in map(int, input().split()):
    cur += X
    if cur == N+1: cur = 1
    if cur == 0: cur = N
    if cur == S: RES += 1
if S == 1: print(RES+1)
else: print(RES)
