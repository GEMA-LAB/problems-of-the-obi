#!/usr/bin/env python3

# Literalmente a solução do autor, adaptada para Python 3

import sys
import itertools

inf = int(1e9 + 5)

melhores_tempos = [[[(inf, inf) for _ in range(2)] for _ in range(4)] for _ in range(2)]

n = int(input())

meninos = 0
tempos = []

for i in range(n):
    modalidade, *tempos_estilos = map(int, input().split())
    if not tempos_estilos:
        tempos_estilos = list(map(int, sys.stdin.readline().split()))
    meninos += modalidade
    for estilo in range(4):
        tempo_estilo = tempos_estilos[estilo]
        if tempo_estilo <= melhores_tempos[modalidade][estilo][0][1]:
            melhores_tempos[modalidade][estilo][1] = melhores_tempos[modalidade][estilo][0]
            melhores_tempos[modalidade][estilo][0] = (i, tempo_estilo)
        elif tempo_estilo <= melhores_tempos[modalidade][estilo][1][1]:
            melhores_tempos[modalidade][estilo][1] = (i, tempo_estilo)

if meninos < 2 or (n - meninos) < 2:
    print(-1)
    sys.exit(0)

combinacao = [0, 1, 2, 3]
menor = -1

for perm in itertools.permutations(combinacao):
    f1, f2, m1, m2 = perm

    # Feminino (modalidade 0)
    if melhores_tempos[0][f1][0][0] != melhores_tempos[0][f2][0][0]:
        f_total = melhores_tempos[0][f1][0][1] + melhores_tempos[0][f2][0][1]
    else:
        aux1 = melhores_tempos[0][f1][0][1] + melhores_tempos[0][f2][1][1]
        aux2 = melhores_tempos[0][f1][1][1] + melhores_tempos[0][f2][0][1]
        f_total = min(aux1, aux2)

    # Masculino (modalidade 1)
    if melhores_tempos[1][m1][0][0] != melhores_tempos[1][m2][0][0]:
        m_total = melhores_tempos[1][m1][0][1] + melhores_tempos[1][m2][0][1]
    else:
        aux1 = melhores_tempos[1][m1][0][1] + melhores_tempos[1][m2][1][1]
        aux2 = melhores_tempos[1][m1][1][1] + melhores_tempos[1][m2][0][1]
        m_total = min(aux1, aux2)

    total = f_total + m_total
    if menor == -1 or menor >= total:
        menor = total

print(menor)