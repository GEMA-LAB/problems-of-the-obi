#!/usr/bin/env python3

# OBI2021 - Fase 2
# Senha da vó Zinha

[n, m, k] = [int(i) for i in input().split()]

# constrói lista de caracteres da senha
s = [c for c in input()]

pos = [] # posições das letras borradas
palavras = [] # palavras com possíveis letras para a senha

for i in range(n):
    if s[i] == '#':
        pos.append(i)

for i in range(m):
    # para cada palavra, constrói a lista de caracteres
    # da palavra, para poder ordenar
    palavras.append([c for c in input()])

x = int(input())


if m == 1:
    # ordena as letras
    palavras[0].sort()
    # substitui o caractere '#' pela x-ésima letra
    s[pos[0]] = palavras[0][x - 1]
    print("".join(s))
else:
    x = x - 1
    # ordena as letras das palavras
    for i in range(m):
      palavras[i].sort()
    for i in range(m):
      s[pos[i]] = palavras[i][0];
    for i in range(m - 1, -1, -1):
      if x == 0:
          break
      tmp = x % k;
      s[pos[i]] = palavras[i][tmp];
      x //= k;

    print("".join(s))
    
