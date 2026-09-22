#!/usr/bin/env python3


n = int(input())
palavra1 = input().strip()
palavra2 = input().strip()
alfabeto = 'abcdefghijklmnopqrstuvwxyz'

letras1 = {c: 0 for c in alfabeto}
letras2 = {c: 0 for c in alfabeto}

for i in palavra1:
    if i not in (' ', ',', '.'):
        letras1[i] += 1

for i in palavra2:
    if i not in (' ', ',', '.'):
        letras2[i] += 1

if letras1 == letras2:
    print('S')
else:
    print('N')
