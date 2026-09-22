#!/usr/bin/env python3

# OBI2023
# Tarefa Epidemia
# r. anido

n = int(input())
r = int(input())
p = int(input())

total = n
dias = 0
while total < p:
    n *= r
    total += n
    dias += 1;

print(dias)
