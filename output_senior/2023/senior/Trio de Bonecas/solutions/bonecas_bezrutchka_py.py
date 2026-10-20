#! /usr/bin/env python3

"""
 * OBI 2023 - Fase 3
 * Trio de Bonecas - Solução O(NK) com Programação Dinâmica
 * Mateus Bezrutchka
 *
 * Ordenamos as bonecas em ordem crescente.
 * Seja dp[i][j] a resposta para as bonecas de j a N formando j trios.
 *
 * Vamos analisar a transição da DP:
 * -> Se a boneca i não pertence a um dos trios, temos
 *      dp[i][j] = dp[i + 1][j].
 *
 * -> Se a boneca i pertence a um trio, então ela é a menor desse trio
 *    (ainda não estamos incluindo as bonecas menores que ela).
 *    Podemos provar, por um argumento de troca, que a opção gulosa de
 *    usar a boneca i + 1 no mesmo trio que a boneca i é ótima:
 *    Se uma solução contém os trios (i, a, b) e (i + 1, c, d),
 *    podemos trocá-los pelos trios (i, i + 1, b) e (a, c, d) sem piorar
 *    a resposta, pois necessariamente c > a > i + 1 > i.
 *    Logo, usando a boneca i + 1,
 *      dp[i][j] = (t[i + 1] - t[i])^2 + dp[i + 2][j - 1].
 *
 * -> Observe que, na transição acima, só escolhemos as duas menores
 *    bonecas de cada trio. Para a maior, podemos escolher qualquer
 *    boneca maior ou igual às duas, mas precisamos garantir que temos
 *    bonecas o suficiente. Isso é simples -- temos bonecas suficientes
 *    se e somente se
 *      3j <= N + 1 - i.
 *    Então basta setar para INF todos os estados que não satisfazem
 *    essa desigualdade, e tirar o mínimo dos dois casos acima.
 *
 * A resposta final é dp[1][K].
"""

def read_int_list():
  return [int(x) for x in input().split()]

INF = int(1e18) + 10

n, k = read_int_list()
t = [0] + read_int_list() # 1-indexed
t.sort()

dp = [[INF for j in range(k + 10)] for i in range(n + 10)]

for i in range(n, 0, -1):
  for j in range(k + 1):

    if i > n - 2:
      # ainda nao da pra formar nenhum trio
      dp[i][j] = 0 if j == 0 else INF
      continue

    if 3 * j > n + 1 - i:
      # nao temos bonecas suficientes
      dp[i][j] = INF
      continue

    sem_boneca = dp[i + 1][j]
    com_boneca = (t[i + 1] - t[i]) * (t[i + 1] - t[i]) + dp[i + 2][j - 1]
    dp[i][j] = min(sem_boneca, com_boneca)

print(dp[1][k])

