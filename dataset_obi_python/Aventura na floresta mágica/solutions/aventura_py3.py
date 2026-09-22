#!/usr/bin/env python3

def posicao(direcao, passos, x, y):
    if direcao == 0:  # Norte
        y += passos
    elif direcao == 90:  # Leste
        x += passos
    elif direcao == 180:  # Sul
        y -= passos
    elif direcao == 270:  # Oeste
        x -= passos
    return x, y


x, y = 0, 0
direcao = 0  # Norte


i = int(input())
for t in range(i):
  d = input()
  p = int(input())
  if d == "M":
     x, y = posicao(direcao, p, x, y)
  elif d == "G":
     direcao = (direcao + p) % 360
     
print(f"{x} {y}")
