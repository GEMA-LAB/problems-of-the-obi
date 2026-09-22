#! /usr/bin/env python3

"""
 * OBI 2023 - Fase 3
 * Tesouro da Quadradônia - Solução O(N^2) usando matriz auxiliar
 *                          para marcar posições visitadas
 * Mateus Bezrutchka
"""

N = int(input())
mapa = [str(input()) for i in range(N)]
[A, B] = [int(x) for x in input().split()]

# marca quais areas eu ja visitei antes para identificar loop infinito
visitado = [[False for k in range(N)] for i in range(N)]

# indexando do 0
x = A - 1
y = B - 1
minutos = 0

agua = False
loop = False

while True:
  if x < 0 or x >= N or y < 0 or y >= N:
    agua = True
    break

  if visitado[x][y]:
    loop = True
    break

  if mapa[x][y] == 'X':
    # encontrou o tesouro
    break

  # move pra próxima área
  visitado[x][y] = True
  minutos += 1
  if mapa[x][y] == 'N':
    x -= 1
  elif mapa[x][y] == 'S':
    x += 1
  elif mapa[x][y] == 'O':
    y -= 1
  else:
    y += 1


if agua:
  print(-1)
elif loop:
  print(0)
else:
  print(minutos)
