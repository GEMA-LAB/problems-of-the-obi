#!/usr/bin/env python3

#   OBI 2025 - Fase 1
#   Dieta

n, m = map(int, input().split())

calorias = 0
for i in range(n):
    p, g, c = map(int, input().split())
    calorias += 4*p + 9*g + 4*c
print(m - calorias)