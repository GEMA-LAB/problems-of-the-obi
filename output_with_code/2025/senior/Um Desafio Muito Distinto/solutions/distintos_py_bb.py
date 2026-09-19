#! /usr/bin/env python3


def solve():
  limite, a, b = map(int, input().split())

  def prefix_sum(x):
    # 1 + 2 + ... + x
    return (x * (x + 1)) / 2

  # verifica se eu consigo completar esse numero de rounds
  # sem chegar no limite
  def check(rounds):
    if rounds > b - a + 1:
      return False
    # algoritmo guloso:
    # sempre eh otimo pegar (a) + (a + 1) + ... + (a + rounds - 1)
    interval_sum = prefix_sum(a + rounds - 1) - prefix_sum(a - 1)
    return interval_sum < limite

  # busca binaria na resposta para encontrar
  # o numero de rodadas que consigo ficar < limite
  # invariante: check(l) é sempre true
  l, r = 0, b + 1
  while l < r:
    m = (l + r + 1) // 2
    if check(m):
      l = m
    else:
      r = m - 1

  if l < b - a + 1:
    # sobrou algum valor pra eu fazer minha ultima rodada
    print(l + 1)
  else:
    # conseguimos usar todos os numeros entre a e b sem exceder o limite
    print(l)


p = int(input())
for i in range(p):
  solve()

