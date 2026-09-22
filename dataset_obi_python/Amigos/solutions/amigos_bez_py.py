#!/usr/bin/env python3

"""
OBI 2024 - Fase 3
  Amigos
  Solução em O(N)

  A observação principal neste problema é de nunca é
  ótimo um integrante do grupo fazer uma troca com um
  outro integrante do grupo (pois essa troca não mudaria
  em nada as posições dos integrantes). Portanto, os
  integrantes em cada lado da mesa se mantêm sempre na
  mesma ordem (entre eles) que estavam no início.

  Assim, o seguinte algoritmo guloso funciona:
  Pareie os integrantes em cada lado da esquerda para
  a direita, ou seja: o primeiro integrante do lado
  superior com o primeiro do lado inferior, o segundo
  do lado superior com o segundo do lado inferior, e
  assim em diante. Basta então somar as distâncias
  de cada par.

  Uma prova formal de que o algoritmo guloso está
  correto pode ser feita com argumento de troca.
"""

[n, k] = [int(x) for x in input().split()]
a = [int(x) for x in input().split()]
b = [int(x) for x in input().split()]

resp = 0
pos_b = 0
for i in range(n):
  if a[i] == 0:
    continue
  while b[pos_b] == 0:
    pos_b += 1

  # encontrei um par de integrantes
  resp += abs(i - pos_b)
  pos_b += 1

print(resp)
