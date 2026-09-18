#! /usr/bin/env python3

# OBI2023
# Tarefa Pizza
# r. anido

n = int(input())
g = int(input())
m = int(input())

sobra = g*8 + m*6 -n
if sobra < 0:
    sobra = 0
print(sobra)
