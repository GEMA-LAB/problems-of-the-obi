// OBI 2023 - Fase 2
// Barcos - Solução com LCA + MST
// Mateus Bezrutchka
// 
// Interpretamos o arquipélago como um grafo.
// 
// -- Solução para árvores (subtarefas 2 e 3) --
// - No caso em que o grafo é uma linha (segunda subtarefa), o problema é
// equivalente a calcular RMQ (Range Minimum Query) em um vetor, o que é
// um problema clássico que pode ser feito em O(log N) por query.
// 
// - No caso em que o grafo é uma árvore (terceira subtarefa), podemos
// usar o algoritmo LCA (Lowest Common Ancestor) para de novo obter O(log N)
// por query: o caminho A -> B em uma árvore pode ser decomposto em A -> LCA
// e LCA -> B, e os mínimos de cada parte podem ser computados se, além do
// vértice, guardarmos na DP do LCA o RMQ do caminho.
// 
// 
// -- Solução para só uma consulta (subtarefa 4) --
// Vamos resolver o caso em que só precisamos responder uma única consulta.
// Chamamos de MST uma Maximum Spanning Tree (ou Árvore Geradora Máxima) do
// grafo -- ou seja, uma árvore com todos os vértices do grafo original e de
// máximo custo total (ou, no caso desse problema, capacidade). Podemos provar
// -- usando o mesmo argumento de substituição ("cut-and-paste") da prova do
// algoritmo de Prim -- que é suficiente só considerar caminhos na MST: se o
// caminho de capacidade máxima não estivesse na MST, poderiamos aumentar a
// capacidade da MST usando ele (contradição).
// 
// Encontrar uma Minimum Spanning Tree do grafo é um problema tradicional, e
// é fácil adaptar algoritmos clássicos (aqui usamos Prim) para nosso caso de
// custo máximo. Portanto, podemos resolver essa subtarefa encontrando uma MST
// e responder a consulta calculando em O(N) o mínimo do caminho X -> Y na MST.
// 
// 
// -- Solução completa (subtarefa 5) --
// Para resolver o problema geral, perceba que só precisamos combinar essas duas
// soluções: preprocessamos encontrando a MST com Prim e, então, usamos LCA com
// RMQ nessa árvore para responder cada consulta em O(log N).
//
// Complexidade: O((B + C) log N).
//
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

typedef pair<int, int> pii;

const int INF = (int)1e9 + 10;
const int MAXN = 100100;
const int MAXLOG = 20;

int n, m, q;
vector <pii> graph[MAXN]; // par (vertice, capacidade da aresta)

set<pii> active_nodes; // par (-max_cap, vertice)
// MST
int max_cap[MAXN];
bool processed[MAXN];
int depth[MAXN];
int parent[MAXN];
int parent_cap[MAXN];

// DP do LCA (sparse table)
int dp_v[MAXLOG][MAXN]; // vertice
int dp_cap[MAXLOG][MAXN]; // capacidade minima no caminho

void prim() {
  // origem pode ser qualquer vertice
  max_cap[1] = 0;
  active_nodes.insert(make_pair(0, 1));
  for (int v = 2; v <= n; v++) {
    max_cap[v] = -INF;
    active_nodes.insert(make_pair(INF, v));
  }

  for (int step = 1; step <= n; step++) {
    pii cur = *active_nodes.begin();
    active_nodes.erase(cur);

    int v = cur.second;
    parent_cap[v] = -cur.first;
    processed[v] = true;
    
    for (int i = 0; i < (int) graph[v].size(); i++) {
      int w = graph[v][i].first;
      int cur_cap = graph[v][i].second;
      if (processed[w]) continue;
      
      // modificacao pra usar arestas de maior capacidade
      if (max_cap[w] < cur_cap) {
        active_nodes.erase(make_pair(-max_cap[w], w));
        max_cap[w] = cur_cap;
        parent[w] = v;
        depth[w] = depth[v] + 1;
        active_nodes.insert(make_pair(-max_cap[w], w));
      }
    }
  }
}

void build_lca_dp() {
  dp_v[0][1] = 1;
  dp_cap[0][1] = INF;
  for (int i = 2; i <= n; i++) {
    dp_v[0][i] = parent[i];
    dp_cap[0][i] = parent_cap[i];
  }

  for (int k = 1; k < MAXLOG; k++) {
    for (int i = 1; i <= n; i++) {
      dp_v[k][i] = dp_v[k - 1][ dp_v[k - 1][i] ];
      dp_cap[k][i] = min(dp_cap[k - 1][i], dp_cap[k - 1][ dp_v[k - 1][i] ]);
    }
  }
}

// encontra a menor capacidade no caminho de a pra b usando LCA
int find_min_cap(int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);

  int ans = INF;
  for (int k = MAXLOG - 1; k >= 0; k--) {
    int nxt_a = dp_v[k][a];
    if (depth[nxt_a] >= depth[b]) {
      ans = min(ans, dp_cap[k][a]);
      a = nxt_a;
    }
  }
  if (a == b) return ans; // b eh ancestral de a

  for (int k = MAXLOG - 1; k >= 0; k--) {
    int nxt_a = dp_v[k][a];
    int nxt_b = dp_v[k][b];
    if (nxt_a != nxt_b) {
      ans = min(ans, min(dp_cap[k][a], dp_cap[k][b]));
      a = nxt_a;
      b = nxt_b;
    }
  }
  // a essa altura, dp_v[0][a] guarda o LCA dos dois
  ans = min(ans, min(dp_cap[0][a], dp_cap[0][b]));

  return ans;
}

int main() {
  int a, b, c;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &a, &b, &c);
    graph[a].push_back(make_pair(b, c));
    graph[b].push_back(make_pair(a, c));
  }

  prim();
  build_lca_dp();

  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    scanf("%d %d", &a, &b);
    printf("%d\n", find_min_cap(a, b));
  }
  return 0;
}
