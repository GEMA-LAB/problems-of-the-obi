#!/usr/bin/env python3

frase = input()
divertido = 0
chateado = 0

# conta numero de divertidos
i = frase.find(':-)')
while i >= 0 and i < len(frase):
    i += 3
    divertido += 1
    i = frase.find(':-)',i)

# conta numero de chateados
i = frase.find(':-(')
while i >= 0 and i < len(frase):
    i += 3
    chateado += 1
    i = frase.find(':-(',i)

if divertido > chateado:
    print('divertido')
elif divertido < chateado:
    print('chateado')
else:
    print('neutro')
