#!/usr/bin/env python3

[n] = [int(x) for x in input().split()]
if n == 2:
  resp = [0, 0, 0, 8]
else:
  resp = [
    (n - 2) * (n - 2) * (n - 2),
    6 * (n - 2) * (n - 2),
    12 * (n - 2),
    8,
  ]
for x in resp:
  print(x)
