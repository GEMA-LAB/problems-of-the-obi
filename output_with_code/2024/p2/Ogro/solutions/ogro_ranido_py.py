#!/usr/bin/env python3

# OBI2024
# Fase 1
# Ogro

e = int(input())
d = int(input())

if e > d:
  res = e + d
else:
  res = 2 * (d - e)

print(res)
