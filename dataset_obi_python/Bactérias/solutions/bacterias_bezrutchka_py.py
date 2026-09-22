#!/usr/bin/env python3

n = int(input())
p = int(input())

pot = 1
r = 0
while True:
  if pot * p > n:
    break
  pot *= p
  r = r + 1

print(r)
