#!/usr/bin/env python3

N = int(input())

lado = 2
for i in range(N):
    lado += lado-1

print( lado**2 )
