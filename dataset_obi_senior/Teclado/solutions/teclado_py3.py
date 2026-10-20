#!/usr/bin/env python3

# OBI2021 - Fase 3
# Teclado

repr = {'2': 'abc',
        '3': 'def',
        '4': 'ghi',
        '5': 'jkl',
        '6': 'mno',
        '7': 'pqrs',
        '8': 'tuv',
        '9': 'wxyz'}


num = input()
m = int(input())

resp = 0
for i in range(m):
    palavra = input()
    if len(palavra) != len(num):
        continue
    ok = True
    for k in range(len(num)):
        if palavra[k] not in repr[num[k]]:
            ok = False
            break
    if ok:
        resp += 1

print(resp)
