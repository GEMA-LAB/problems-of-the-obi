#!/usr/bin/env python3

# OBI2022
# Tarefa Chuva

MAX = 10**6
N = int(input())
S = int(input())

vetor = [int(x) for x in input().split()]
resp = 0

somas = [0 for i in range(MAX)]
soma = 0;
somas[0] = 1;

for v in vetor:
    soma += v
    if soma - S >= 0:
        resp += somas[soma - S]
    somas[soma] += 1

print(resp)


