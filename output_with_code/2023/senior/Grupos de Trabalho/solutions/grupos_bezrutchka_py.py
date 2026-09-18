#! /usr/bin/env python3

# OBI 2023 - Fase 2
# Grupos - Solução linear com vetor de marcação
# Mateus Bezrutchka

# le uma linha que representa uma lista de inteiros
def int_readline():
  return [int(x) for x in input().split()]

e, m, d = int_readline()

juntos = []
separados = []
for i in range(m):
  juntos.append(int_readline())
for i in range(d):
  separados.append(int_readline())

# vamos guardar, para cada estudante, o indice do grupo dele
grupo = [-1 for i in range(e + 1)]
for i in range(int(e / 3)):
  a, b, c = int_readline()
  grupo[a] = i
  grupo[b] = i
  grupo[c] = i

# agora checamos todas as violações
num_violacoes = 0

for i in range(m):
  a = juntos[i][0]
  b = juntos[i][1]
  if grupo[a] != grupo[b]:
    num_violacoes += 1

for i in range(d):
  a = separados[i][0]
  b = separados[i][1]
  if grupo[a] == grupo[b]:
    num_violacoes += 1

print(num_violacoes)
