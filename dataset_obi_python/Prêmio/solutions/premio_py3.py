#!/usr/bin/env python3

# OBI2023
# Tarefa Prêmio
# r. anido

p = int(input())
d = int(input())
b = int(input())


pontos = p + 2*d + 3*b

if pontos >= 150:
    print('B')
elif pontos >= 120:
    print('D')
elif pontos >= 100:
    print('P')
else:
    print('N')

