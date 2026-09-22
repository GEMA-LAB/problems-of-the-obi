#!/usr/bin/env python3

n = int(input())
posicao_no_ranking = [0 for i in range(n + 1)]

for posicao in range(1, n + 1):
  atleta = int(input())
  posicao_no_ranking[atleta] = posicao

for atleta in range(1, n + 1):
  print(posicao_no_ranking[atleta])
