#!/usr/bin/env python3


palavra = input().strip()

alfabeto = "abcdefghijlmnopqrstuvxz"

letras = set()
for i in palavra:
    if i in alfabeto:
        letras.add(i)

if len(letras) == len(alfabeto):
    print('S')
else:
    print('N')
