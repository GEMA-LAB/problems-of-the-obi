#!/usr/bin/env python3

d = int(input())

resp = 2000
ponto = 0
while ponto <= 2000:
  if d > ponto:
    dist_ponto = d - ponto
  else:
    dist_ponto = ponto - d
  resp = min(resp, dist_ponto)
  ponto += 400

print(resp)
