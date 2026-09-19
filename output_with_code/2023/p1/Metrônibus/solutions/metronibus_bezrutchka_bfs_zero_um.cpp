/**
 *
 * OBI 2023 - Fase 3
 * Metrônibus - Solução O(N + K1 + K2) com BFS 0-1
 * Mateus Bezrutchka
 *
 * Modelamos o problema usando um grafo novo baseado no original:
 * - Cada estação vira dois vértices: um para metrô e um para ônibus;
 * - Cada ligação vira uma aresta com peso 0 entre os vértices do
 *   respectivo sistema;
 * - Adicionamos uma aresta de peso 1 entre os dois vértices representando
 *   a mesma estação.
 *
 * Dessa forma, o número mínimo de trocas de sistema é o tamanho do caminho
 * mínimo entre um dos vértices de início (temos 2) e um dos vértices de fim.
 *
 * Esse caminho mínimo pode ser encontrado usando BFS 0-1.
 **/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

const int MAXN = 200100; // 2 * N porque vamos duplicar o grafo
const int INF = (int)1e9 + 10;

int n, K[2], P, A, B;

vector <pii> graph[MAXN]; // lista de adj
int dist[MAXN];
queue <int> q0, q1;

// 2v-1 pra metro, 2v pra onibus
int vtx(int s, int v) {
  return 2 * v - 1 + s;
}

// retorna a distância mínima pra um dos componentes da estação B
int bfs_01(int origin) {
  while (!q0.empty()) q0.pop();
  while (!q1.empty()) q1.pop();
  for (int v = 1; v <= n; v++) {
    dist[v] = INF;
  }
  dist[origin] = 1;
  q0.push(origin);

  while (!q0.empty()) {
    int v = q0.front();
    q0.pop();

    for (int k = 0; k < (int) graph[v].size(); k++) {
      int w = graph[v][k].first;
      int d = graph[v][k].second;
      if (dist[w] < INF) continue;
      dist[w] = dist[v] + d;
      if (d == 0) q0.push(w);
      else q1.push(w);
    }

    if (q0.empty()) {
      swap(q0, q1);
    }
  }

  return min(dist[vtx(0, B)], dist[vtx(1, B)]);
}

int main() {
  // le entrada
  cin >> n >> K[0] >> K[1] >> P;
  for (int s = 0; s < 2; s++) {
    while (K[s]--) {
      int v, u;
      cin >> v >> u;
      graph[vtx(s, v)].push_back(make_pair(vtx(s, u), 0));
      graph[vtx(s, u)].push_back(make_pair(vtx(s, v), 0));
    }
  }
  cin >> A >> B;

  // adiciona arestas de peso 1
  for (int v = 1; v <= n; v++) {
    graph[vtx(0, v)].push_back(make_pair(vtx(1, v), 1));
    graph[vtx(1, v)].push_back(make_pair(vtx(0, v), 1));
  }
  n *= 2; // nao precisamos mais do n original

  int mresp = bfs_01(vtx(0, A)); // começando no metro
  int oresp = bfs_01(vtx(1, A)); // começando no onibus
  if (mresp == INF && oresp == INF) {
    cout << -1 << endl;
  } else {
    cout << min(mresp, oresp) * P << endl;
  }
  return 0;
}
