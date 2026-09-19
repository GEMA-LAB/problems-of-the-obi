#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> pip;

const int MAXN = 1e5 + 10;
int dsu_parent[MAXN];
int dsu_depth[MAXN];

void dsu_init(int n) {
  for (int i = 1; i <= n; i++) {
    dsu_parent[i] = i;
    dsu_depth[i] = 0;
  }
}

int dsu_find(int v) {
  if (v == dsu_parent[v]) return v;
  return dsu_parent[v] = dsu_find(dsu_parent[v]);
}

bool dsu_union(int u, int v) {
  u = dsu_find(u);
  v = dsu_find(v);
  if (u == v) {
    return false;
  }
  if (dsu_depth[u] < dsu_depth[v]) {
    swap(u, v);
  }
  dsu_parent[v] = u;
  if (dsu_depth[u] == dsu_depth[v]) {
    dsu_depth[u]++;
  }
  return true;
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<pip> edges;
  while (m--) {
    int a, b, t;
    cin >> a >> b >> t;
    edges.push_back({t, {a, b}});
  }

  dsu_init(n);
  sort(edges.begin(), edges.end());
  int min_removals = 0;
  bool hydro_cycle = false;
  for (auto edge: edges) {
    int t = edge.first, a = edge.second.first, b = edge.second.second;
    bool ret = dsu_union(a, b);
    if (ret == false) {
      if (t == 1) hydro_cycle = true;
      else min_removals++;
    }
  }

  if (hydro_cycle) {
    cout << "N" << endl;
  } else if (min_removals > k) {
    cout << "N" << endl;
  } else {
    cout << "S" << endl;
  }
  return 0;
}
