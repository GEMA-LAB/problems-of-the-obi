#!/usr/bin/env python3

# OBI 2025 - Fase 1
# Cafeteria

a = int(input())
b = int(input())
c = int(input())
d = int(input())

# pra ter no minimo a de leite, doses precisam ser no maximo isso
# (divisao inteira arredonda pra baixo)
max_doses = (c - a) // d

# pra ter no maximo b de leite, doses precisam ser no minimo isso
# (soma d - 1 pra divisao inteira arredondar pra cima)
min_doses = (c - b + d - 1) // d

if min_doses <= max_doses:
  print("S")
else:
  print("N")
