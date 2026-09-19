#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 20;

int n, m;
bool usado[MAXN];
vector <int> proibido[MAXN];

int calc (int x) {
  if (x == n) return 1;
  int ret = calc(x+1);

  bool ok = 1;
  for (auto v: proibido[x])
    if (usado[v]) ok = 0;

  if (ok){
    usado[x] = 1;
    ret += calc(x+1);
    usado[x] = 0;
  }

  return ret;
}

int main (void){
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int x, y; scanf("%d%d", &x, &y);
    --x; --y; 
    proibido[x].push_back(y);
    proibido[y].push_back(x);
  }

  printf("%d\n", calc(0) - 1);
  return 0;
}
