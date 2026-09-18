#!/usr/bin/env python3

[n, q] = [int(x) for x in input().split()]
v = [int(x) for x in input().split()]

psum = []
soma = 0
for x in v:
  soma += x
  psum.append(soma)

while q > 0:
  [l, r] = [int(x) for x in input().split()]
  l -= 1
  r -= 1
  tam = r - l + 1
  if l == 0:
    soma = psum[r]
  else:
    soma = psum[r] - psum[l - 1]
  resp = (tam - 1) * soma * 11
  print(resp)
  q -= 1

