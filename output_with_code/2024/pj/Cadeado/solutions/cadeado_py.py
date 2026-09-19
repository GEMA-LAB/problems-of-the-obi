#!/usr/bin/env python3

"""
OBI 2024 - Fase 3
  Cadeado
  Solução em O(N) com iteração e análise de casos
"""

n = int(input())
clicks = 0

for i in range(n):
  c, s = map(int, input().split())
  if s < c:
    hor = c - s
    anti_hor = 10 + s - c
    clicks += min(hor, anti_hor)
  else:
    anti_hor = s - c
    hor = 10 + c - s
    clicks += min(hor, anti_hor)

print(clicks)
