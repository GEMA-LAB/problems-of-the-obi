#!/usr/bin/env python3

# OBI 2025 - Fase 1
# Cafeteria

a = int(input())
b = int(input())
c = int(input())
d = int(input())

possivel = False
doses = 1

# testa todas as quantidades de doses
while doses * d <= c:
  leite = c - doses * d
  if a <= leite and leite <= b:
    possivel = True
  doses += 1

if possivel:
  print("S")
else:
  print("N")
