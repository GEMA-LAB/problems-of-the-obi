#!/usr/bin/env python3

# OBI 2025 - Fase 1
# Cafe com Leite

a = int(input())
b = int(input())
c = int(input())
d = int(input())

if a <= c - d and c - d <= b:
  print("S")
else:
  print("N")
