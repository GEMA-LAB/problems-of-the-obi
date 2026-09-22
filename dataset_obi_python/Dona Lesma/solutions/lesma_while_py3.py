#!/usr/bin/env python3

# OBI2020
# dona lesma

a = int(input())
s = int(input())
d = int(input())

distancia = 0
dias = 0
while True:
    dias += 1
    distancia = distancia + s
    if distancia >= a:
        break
    distancia = distancia - d

print(dias)
