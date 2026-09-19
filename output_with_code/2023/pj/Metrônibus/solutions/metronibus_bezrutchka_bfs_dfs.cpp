/**
 * OBI 2023 - Fase 3
 * Metrônibus - Solução O(N + K1 + K2) com BFS e DFS
 * Mateus Bezrutchka
 * 
 * Modelamos o problema usando um grafo novo baseado no original, onde
 * cada estação vira dois vértices: um para metrô e um para ônibus, com
 * as arestas conectando somente os vértices do sistema correspondente.
 * 
 * Assim, podemos encontrar a resposta rodando uma BFS modificada nos
 * dois candidatos a vértice inicial (um de metrô e um de ônibus):
 * Toda vez que processamos um vértice na BFS, também processamos todos
 * os vértices da componente conexa dele (já que todos podem ser alcançados
 * sem pagar nada).
 **/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 200100; // 2 * N porque vamos duplicar o grafo
const int INF = (int)1e9 + 10;

int n, K[2], P, A, B;
vector <int> graph[MAXN]; // lista de adj
int dist[MAXN];
queue <int> q;

int vtx(int s, int v) { 
  return 2 * v - 1 + s;
}

int other_vtx(int v) { // o outro vértice representando a mesma estação
  return (v % 2 == 1) ? v + 1 : v - 1;
}

void dfs(int v, int d) {
  dist[v] = d;
  // coloca o outro vértice da estação na fila da BFS
  int w = other_vtx(v);
  if (dist[w] == INF) {
    dist[w] = d + 1;
    q.push(w);
  }

  for (int i = 0; i < (int) graph[v].size(); i++) {
    int w = graph[v][i];
    if (dist[w] < INF) continue;
    dfs(w, d);
  }
}

// retorna a distância mínima pra estação B
int bfs(int origin) {
  while (!q.empty()) q.pop();
  for (int v = 1; v <= n; v++) {
    dist[v] = INF;
  }
  dist[origin] = 1;
  q.push(origin);

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    dfs(v, dist[v]); // processa componente
  }
  return min(dist[vtx(0, B)], dist[vtx(1, B)]);
}

int main() {
  cin >> n >> K[0] >> K[1] >> P;
  for (int s = 0; s < 2; s++) {
    while (K[s]--) {
      int v, u;
      cin >> v >> u;
      graph[vtx(s, v)].push_back(vtx(s, u));
      graph[vtx(s, u)].push_back(vtx(s, v));
    }
  }
  cin >> A >> B;
  n = 2 * n; // não precisamos mais do n original

  int mresp = bfs(vtx(0, A)); // começando no metro
  int oresp = bfs(vtx(1, A)); // começando no onibus
  if (mresp == INF && oresp == INF) {
    cout << -1 << endl;
  } else {
    cout << min(mresp, oresp) * P << endl;
  }
  return 0;
}
