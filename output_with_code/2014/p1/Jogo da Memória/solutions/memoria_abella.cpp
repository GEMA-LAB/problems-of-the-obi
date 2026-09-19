#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>

typedef long long lint;

using namespace std;

int n, logn;
vector< pair <int, int> > query;
vector< vector<int> > adj;
vector<int> height;
vector< vector<int> > parent;

void dfs(int v, int p) {
  for (int l = 1; l <= logn; l++)
    parent[v][l] = parent[parent[v][l-1]][l-1];

  for (int i = 0; i < (int)adj[v].size(); i++) {
    int v2 = adj[v][i];
    if (v2 == p) continue;
    height[v2] = height[v] + 1;
    parent[v2][0] = v;
    dfs(v2, v);
  }
}

int goup(int a, int dist) {
  for (int l = 0; dist; l++)
    if (dist & (1<<l)) {
      a = parent[a][l];
      dist -= (1<<l);
    }
  return a;
}

int lca(int a, int b) {
  if (height[a] < height[b]) swap(a, b);
  a = goup(a, height[a] - height[b]);
  if (a == b) return a;
  for (int l = logn; l >= 0; l--)
    if (parent[a][l] != parent[b][l])
      a = parent[a][l], b = parent[b][l];
  return parent[a][0];
}

int dist(int a, int b) {
  return height[a] + height[b] - 2 * height[lca(a, b)];
}

int main() {
  cin >> n;
  logn = 0;
  while ((1 << (logn+1)) <= n) logn++;

  query = vector< pair <int, int> >(n);
  for (int i = 0; i < n; i++) {
    int v;
    cin >> v; v--;
    query[v].second = query[v].first;
    query[v].first = i;
  }
  
  adj = vector< vector<int> >(n);
  for (int i = 0; i < n-1; i++) {
    int a, b;
    cin >> a >> b; a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  parent = vector< vector<int> >(n, vector<int>(logn+1));

  height = vector<int>(n);
  height[0] = 0;
  parent[0][0] = 0;
  dfs(0, -1);
  
  lint result = 0;

  for (int q = 0; q < n/2; q++) {
    int a = query[q].first, b = query[q].second;
    result += dist(a, b);
  }

  cout << result << endl;

  return 0;
}
