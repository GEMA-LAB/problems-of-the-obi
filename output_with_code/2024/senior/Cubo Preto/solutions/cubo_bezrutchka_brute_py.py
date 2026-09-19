#!/usr/bin/env python3

n = int(input())

resp = [0, 0, 0, 0]
for i in range(n):
  for j in range(n):
    for k in range(n):
      bordas = 0
      if i == 0 or i == n - 1:
        bordas += 1
      if j == 0 or j == n - 1:
        bordas += 1
      if k == 0 or k == n - 1:
        bordas += 1
      resp[bordas] += 1

for x in resp:
  print(x)
