#!/usr/bin/env python3

# OBI2021 - Fase 3
## Falha de segurança

#include <bits/stdc++.h>

MAXN = 20000

senhas = []
contador = {}

n = int(input())

for i in range(n):
    senha = input()
    senhas.append(senha)
    subcadeias = set()
    for j in range(len(senha)):
        corrente = ''
        for k in range(j,len(senha)):
            corrente += senha[k]
            subcadeias.add(corrente)

    for x in subcadeias:
        if x in contador.keys():
            contador[x] += 1
        else:
            contador[x] = 1

resp = 0
for senha in senhas:
    resp += contador[senha]

print(resp - n)


