#!/usr/bin/env python3

pos = {'A':0, 'B': 1, 'C':2}
rpos = {0:'A', 1:'B', 2:'C'}

N = int(input())
moeda = input().strip()

for i in range(N):
    t = int(input())
    if t == 1:
        if moeda == 'A':
            moeda = 'B'
        elif moeda == 'B':
            moeda = 'A'
    elif t == 2:
        if moeda == 'B':
            moeda = 'C'
        elif moeda == 'C':
            moeda = 'B'
    else:
        if moeda == 'A':
            moeda = 'C'
        elif moeda == 'C':
            moeda = 'A'

print(moeda)
