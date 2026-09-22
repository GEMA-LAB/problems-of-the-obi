#!/usr/bin/env python3

eA, eB = input().split()
tA, tB = [float(x) for x in input().split()]

if eA == 'F':
    tA = (tA - 32) * 5 / 9

if eB == 'F':
    tB = (tB - 32) * 5 / 9

if tA < tB:
    print('A')
else:
    print('B')