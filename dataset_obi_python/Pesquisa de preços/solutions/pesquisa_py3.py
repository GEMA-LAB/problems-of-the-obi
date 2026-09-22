#!/usr/bin/env python3

# OBI2021 - Fase 2
# Pesquisa de preços

N = int(input())

existe = False

for i in range(N):
    estado, alcool, gasolina = input().split()
    alcool = float(alcool)
    gasolina = float(gasolina)
    if alcool/gasolina <= 0.70:
        print(estado)
        existe = True

if not existe:
    print('*')

