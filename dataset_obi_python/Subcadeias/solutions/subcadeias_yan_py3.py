#!/usr/bin/env python3

# OBI2022 - Fase 2
# Tarefa Subcadeias
# Yan Silva

n = int(input())
s = input()

resposta = 0

for l in range(n):
    for r in range(l, n):
        eh_palindromo = True
        pl, pr = l, r

        while pl <= pr:
            if s[pl] != s[pr]:
                eh_palindromo = False

            pl = pl + 1
            pr = pr - 1

        if eh_palindromo:
            resposta = max(resposta, r - l + 1)

print(resposta)