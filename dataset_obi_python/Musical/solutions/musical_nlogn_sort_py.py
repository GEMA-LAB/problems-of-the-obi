#!/usr/bin/env python3

"""
OBI 2024 - Fase 3
  Musical
  Solução em O(N log N)

  A observação chave para resolver este problema é a seguinte:
  Dado um intervalo qualquer de músicas distintas, a menor dissonância
  é obtida ao ordenarmos as músicas em ordem crescente ou em ordem
  decrescente de energia, e essa dissonância é
      maior_energia - menor_energia.
  Para visualizar isso, você pode desenhar um gráfico com as energias
  atuais. Uma prova formal pode ser feita com argumento de troca.

  Sabendo disso, temos um limite mínimo para a resposta:
  considerando as músicas de menor e maior energia, existem dois
  intervalos na lista circular que possuem essas duas músicas como
  pontas (o que vai da menor pra maior energia e o que vai da maior
  para a menor), logo, a resposta é no mínimo
    2 * (maior_energia - menor_energia).
  Claramente, este mínimo é atingido se ordenarmos cada um desses
  dois intervalos.
"""

n = int(input())
energias = []

for i in range(n):
  e = int(input())
  energias.append(e)

energias.sort()
maior = energias[n - 1]
menor = energias[0]

print(2 * (maior - menor))
