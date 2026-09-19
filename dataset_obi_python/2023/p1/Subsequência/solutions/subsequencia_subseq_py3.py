#!/usr/bin/env python3

# OBI2023
# Tarefa Subsequência
# r. anido

na, nb = [int(i) for i in input().split()]

a = [int(i) for i in input().split()]
b = [int(i) for i in input().split()]

resp = 'S'
i = 0
j = 0

while True:
    if a[i] == b[j]:
        i += 1
        j += 1
    else:
        i += 1

    if j == len(b):
        break
    if i == len(a):
        resp = 'N'
        break
    

print(resp)
