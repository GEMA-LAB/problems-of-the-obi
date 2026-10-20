#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1e5 + 10;
vector<pii> adj[MAXN];
int comp[2][MAXN], comp_sz[2][MAXN], cur_comp[2];

bool has_hydrocycle = false;

// g = 0: grafo usando somente hidrovias; g = 1: grafo usando todas as arestas
void dfs(int g, int v, int p) {
  comp[g][v] = cur_comp[g];
  for (auto [w, t]: adj[v]) {
    if (g == 0 && t == 2) continue;
    if (w == p) continue;
    if (comp[g][w]) {
      if (g == 0) has_hydrocycle = true;
      continue;
    }
    dfs(g, w, v);
  }
}

int main() {
  int n, m, k;
  int cnt_rod = 0;
  cin >> n >> m >> k;
  while (m--) {
    int a, b, t;
    cin >> a >> b >> t;
    adj[a].push_back({b, t});
    adj[b].push_back({a, t});
    if (t == 2) cnt_rod++;
  }

  for (int g = 0; g < 2; g++) {
    for (int v = 1; v <= n; v++) {
      if (!comp[g][v]) {
        cur_comp[g]++;
        dfs(g, v, 0);
      }
    }
  }

  if (has_hydrocycle) {
    cout << "N" << endl;
    return 0;
  }

  int allowed_edges = cur_comp[0] - cur_comp[1];
  int forbidden_edges = cnt_rod - allowed_edges;
  if (forbidden_edges > k) {
    cout << "N" << endl;
  } else {
    cout << "S" << endl;
  }
  return 0;
}
