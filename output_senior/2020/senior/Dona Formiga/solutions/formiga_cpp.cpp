#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 210;

int S, T, P;
int altura[MAX];
int distancia[MAX];
vector<int> adj[MAX];

int busca(int k) {
  if (distancia[k] == -1) {
    distancia[k] = 0;
    for (auto q : adj[k]) {
      distancia[k] = max(1 + busca(q), distancia[k]);
    }
  }
  return distancia[k];
}

int main(void) {
  int i, a, b;
  
  scanf("%d%d%d", &S, &T, &P);
  for (i=0; i<S; i++)
    scanf("%d", &altura[i]);

  for (i=0; i<T; i++) {
    scanf("%d%d", &a, &b);
    a--; b--;
    if (altura[a] > altura[b])
      adj[a].push_back(b);
    else if (altura[a] < altura[b])
      adj[b].push_back(a);
  }

  memset(distancia, -1, sizeof(distancia));
  printf("%d\n", busca(P-1));
  
  return 0;
}
