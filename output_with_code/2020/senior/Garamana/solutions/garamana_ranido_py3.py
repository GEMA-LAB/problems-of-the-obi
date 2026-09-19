#!/usr/bin/env python3
import string

p = input()
a = input()

letras_p, letras_a = {},{}
for letra in string.ascii_lowercase:
    letras_a[letra] = a.count(letra)
    letras_p[letra] = p.count(letra)

resultado = 'S'
for letra in string.ascii_lowercase:
    if letras_p[letra] < letras_a[letra]:
        resultado = 'N'
        break

print(resultado)
