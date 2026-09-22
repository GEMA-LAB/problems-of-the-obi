#!/usr/bin/env python3


n = int(input())
palavra1 = input().strip()
palavra2 = input().strip()

letras1 = []
for c in palavra1:
    if c not in (' ', ',', '.'):
        letras1.append(c)

letras2 = []
for c in palavra2:
    if c not in (' ', ',', '.'):
        letras2.append(c)

letras1.sort()
letras2.sort()

if letras1 == letras2:
    print('S')
else:
    print('N')
