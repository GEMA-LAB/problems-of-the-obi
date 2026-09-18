/**
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
 **/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<double, double> pdd;

const int MAXN = (int)3e5 + 10;
const int INF = (int)1e9 + 10;
int n;
int x[MAXN], y[MAXN];
pdd point[MAXN];

// (x, y) -> (x + y, x - y)
pdd transform(pdd p) {
  return make_pair(p.first + p.second, p.first - p.second);
}

// (x + y, x - y) -> (x, y)
// usando doubles em tudo porque isso pode nao dar inteiro pros vertices do retangulo
pdd r_transform(pdd p) {
  return make_pair((p.first + p.second) / 2.0, (p.first - p.second) / 2.0);
}

int manhattan_dist(pdd p1, pdd p2) {
  double dx = abs(p1.first - p2.first);
  double dy = abs(p1.second - p2.second);
  return round(dx + dy);
}

int solve() {
  double x_min = INF, x_max = -INF;
  double y_min = INF, y_max = -INF;

  for (int i = 1; i <= n; i++) {
    pdd tp = transform(point[i]);
    x_min = min(x_min, tp.first);
    x_max = max(x_max, tp.first);
    y_min = min(y_min, tp.second);
    y_max = max(y_max, tp.second);
  }

  int ans = INF;
  // testa os dois casos
  for (int t = 1; t <= 2; t++) {
    pdd vertex_1, vertex_2;
    if (t == 1) {
      // caso 1: vertices (superior esquerdo, inferior direito)
      vertex_1 = r_transform(make_pair(x_min, y_max));
      vertex_2 = r_transform(make_pair(x_max, y_min));
    } else {
      // caso 2: vertices (inferior esquerdo, superior direito)
      vertex_1 = r_transform(make_pair(x_min, y_min));
      vertex_2 = r_transform(make_pair(x_max, y_max));
    }

    int cur_ans = 0;
    for (int i = 1; i <= n; i++) {
      int candidate = min(
        manhattan_dist(vertex_1, point[i]),
        manhattan_dist(vertex_2, point[i])
      );
      cur_ans = max(cur_ans, candidate);
    }

    ans = min(ans, cur_ans);
  }

  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &x[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &y[i]);
  }
  for (int i = 1; i <= n; i++) {
    point[i] = make_pair((double) x[i], (double) y[i]);
  }
  printf("%d\n", solve());
  return 0;
}
