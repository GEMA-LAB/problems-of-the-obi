#!/usr/bin/env python3

n = int(input())
posicao_no_ranking = dict()

for posicao in range(1, n + 1):
  atleta = int(input())
  posicao_no_ranking[atleta] = posicao

for atleta in range(1, n + 1):
  print(posicao_no_ranking[atleta])
