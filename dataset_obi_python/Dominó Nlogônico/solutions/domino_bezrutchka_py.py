#! /usr/bin/env python3

"""
 * OBI 2023 - Fase 3
 * Dominó Nlogônico - Solução O(N) usando pilha
 * Mateus Bezrutchka
 *
 * Vamos calcular as respostas da direita para a esquerda.
 * Seja resp[i] a resposta para o dominó i.
 *
 * A todo momento, dizemos que um dominó é "líder" se ainda
 * não existe nenhum dominó à esquerda dele, já processado,
 * que derruba ele. Ao processarmos um dominó que derruba
 * alguns líderes, esse dominó vira líder de todos eles.
 *
 * Observe que
 *    resp[i] = soma(resp[k] para k líder e i derruba k)
 * pois as respostas dos líderes contém todos os dominós
 * que seriam derrubados indiretamente pelo dominó i.
 *
 * Podemos usar uma estrutura de pilha para manter os
 * líderes atuais, e assim calcular todas as respostas em
 * um tempo total de O(N).
 *
"""

def read_int():
  return int(input())

def read_int_list():
  return [int(x) for x in input().split()]

n = read_int()
x = read_int_list()
h = read_int_list()
pilha = []
resp = [-1 for i in range(n)]
tamanho = 0

for i in range(n - 1, -1, -1):
  resp[i] = 1
  while tamanho > 0:
    topo = pilha[tamanho - 1]
    if x[i] + h[i] < x[topo]:
      break
    resp[i] += resp[topo]
    pilha.pop()
    tamanho -= 1
  pilha.append(i)
  tamanho += 1

resp = map(str, resp)
print(" ".join(resp))
