/* Capitais - Felipe Abella */

#include <algorithm>
#include <cstdio>
#include <vector>

#define INF 1000000000
#define MAXN 100000

using namespace std;

int ret;
vector<int> adj[MAXN];

int dfs(int v, int p) {
  if (adj[v].size() == 1) return 0;
  else {
    int mindist = INF;
    for (int i = 0; i < (int)adj[v].size(); ++i) {
      int u = adj[v][i];
      if (u == p) continue;
      int dist = dfs(u, v) + 1;
      ret = min(ret, mindist + dist);
      mindist = min(mindist, dist);
    }
    return mindist;
  }
}

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n-1; ++i) {
    int u, v;
    scanf("%d %d", &u, &v), --u, --v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  if (n == 2) ret = 1;
  else {
    ret = INF;

    for (int i = 0; i < n; ++i)
      if (adj[i].size() > 1) {
	dfs(i, -1);
	break;
      }
  }

  printf("%d\n", ret);
  return 0;
}
