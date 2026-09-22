#! /usr/bin/env python3

"""
 * OBI 2023 - Fase 3
 * Fast-Food - Solução O(N)
 * Mateus Bezrutchka
 * 
 * Para transformar a distância quadradônica (i.e. distância de Manhattan) em
 * uma distância em só uma dimensão, aplicamos a seguinte transformação para o
 * ponto (x, y):
 *    (x, y) -> (x + y, x - y),
 * que é útil dado o fato a seguir.
 * 
 * Fato: Para quaisquer dois pontos (x1, y1) e (x2, y2), temos
 *    |x1 - x2| + |y1 - y2| = max(
 *                            | (x1 + y1) - (x2 + y2) |,
 *                            | (x1 - y1) - (x2 - y2) |).
 * A prova se dá por análise de casos.
 * 
 * Agora, seja ABCD o menor retângulo paralelo aos eixos contendo todos os
 * N pontos após a transformação (chamarei de "fecho retangular"). Observe que,
 * pelo fato acima, a distância de Manhattan máxima entre dois pontos originais
 * equivale à distância máxima entre um ponto e os lados do fecho retangular.
 * 
 * Como cada ponto pertence a um dos dois conjuntos, o fecho retangular de cada
 * conjunto necessariamente contém dois lados (um horizontal e um vertical) do
 * fecho original. Assim, só precisamos calcular duas possibilidades:
 *   - um dos grupos contém os lados AB e BC, e nesse caso a distância máxima
 *     é a distância de Manhattan máxima entre os pontos no grupo e o vértice B
 *     (após sua transformação reversa), enquanto o outro grupo usa o vértice D.
 *   - um dos grupos contêm os lados AB e AD, e nesse caso a distância é
 *     calculada com o ponto A (também após a transformação reversa),
 *     enquanto o outro grupo usa o vértice C.
 * 
 * Assim, basta testar as duas possibilidades e escolher o vértice mais próximo
 * de cada ponto para decidir o conjunto dele.
"""

INF = 1e9 + 10

def read_int_list():
  return [int(x) for x in input().split()]

[n] = read_int_list()
x = read_int_list()
y = read_int_list()
point = [(x[i], y[i]) for i in range(n)]


# (x, y) -> (x + y, x - y)
def transform(p):
  return (p[0] + p[1], p[0] - p[1])

# (x + y, x - y) -> (x, y)
def r_transform(p):
  return ((p[0] + p[1]) / 2.0, (p[0] - p[1]) / 2.0)

def manhattan_dist(p1, p2):
  return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])


tp = list(map(transform, point))
tpx = [p[0] for p in tp]
tpy = [p[1] for p in tp]
x_min, x_max = min(tpx), max(tpx)
y_min, y_max = min(tpy), max(tpy)

ans = INF
# testa os dois casos
for t in range(2):
  vertex_1, vertex_2 = None, None
  if t == 0:
    # caso 1: vertices (superior esquerdo, inferior direito)
    vertex_1 = r_transform((x_min, y_max))
    vertex_2 = r_transform((x_max, y_min))
  else:
    # caso 2: vertices (inferior esquerdo, superior direito)
    vertex_1 = r_transform((x_min, y_min))
    vertex_2 = r_transform((x_max, y_max))

  cur_ans = 0
  for i in range(n):
    d1 = manhattan_dist(vertex_1, point[i])
    d2 = manhattan_dist(vertex_2, point[i])
    cur_ans = max(cur_ans, min(d1, d2))

  ans = min(ans, cur_ans)

print(int(ans))
