#!/usr/bin/env python3

[n, k] = [int(x) for x in input().split()]
vals = [int(x) for x in input().split()]
nota = 100
while nota >= 1:
  cont = 0
  for i in range(n):
    if vals[i] >= nota:
      cont += 1
  if cont >= k:
    print(nota)
    break
  nota -= 1
