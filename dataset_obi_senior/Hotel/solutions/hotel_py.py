#!/usr/bin/env python3

# OBI2022
# Tarefa hotel

d = int(input())
a = int(input())
n = int(input())

# vamos usar chegada para calcular o valor da diária
chegada = n
if chegada > 15:
    chegada = 15

diaria = d + (chegada-1)*a

print((31 - n + 1)*diaria)
