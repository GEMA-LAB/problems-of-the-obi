#!/usr/bin/env python3

# OBI2022
# Tarefa Cinema

resp = 0

# vamos repetir para as duas amigas
for i in range(2):
    x = int(input())
    if x < 18:
        resp += 15
    elif x < 60:
        resp += 30
    else:
        resp += 20

print(resp)
