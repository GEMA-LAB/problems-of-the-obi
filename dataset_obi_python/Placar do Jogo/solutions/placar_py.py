#!/usr/bin/env python3

#   OBI 2025 - Fase 2
#   Placar

maxt = 101

marc = [-1]*maxt

for i in range(2):
    v = list(map(int, input().split()))
    for j in range(1, len(v)):
        marc[v[j]] = i

resp = [0, 0]

print(0, 0)
for x in marc:
    if x != -1:
        resp[x] += 1
        print(resp[0], resp[1])