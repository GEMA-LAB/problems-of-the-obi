#!/usr/bin/env python3

[l, c, t] = [int(x) for x in input().split()]

original = []
for i in range(l):
  original.append([])
  for j in range(c):
    original[i].append(c * i + j + 1)

linha = []
coluna = []
for i in range(l):
  linha.append(i)
for j in range(c):
  coluna.append(j)

for _ in range(t):
  entradas = input().split()
  [op, a, b] = entradas[0], int(entradas[1]), int(entradas[2])
  a -= 1
  b -= 1
  if op == 'L':
    aux = linha[a]
    linha[a] = linha[b]
    linha[b] = aux
  else:
    aux = coluna[a]
    coluna[a] = coluna[b]
    coluna[b] = aux

resposta = []
for i in range(l):
  resposta.append([])
  for j in range(c):
    resposta[i].append(original[linha[i]][coluna[j]])

for resp in resposta:
  saida = " ".join([str(x) for x in resp])
  print(saida)
