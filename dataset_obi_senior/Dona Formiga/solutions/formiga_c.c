// OBI2020
// dona formiga

#include <stdio.h>
#include <string.h>

#define TAM 200

int S, T, P, altura[TAM], max_dist[TAM];
char adj[TAM][TAM];

int busca(int k) {
  int q, tmp;
  
  if (max_dist[k] == -1) {
    max_dist[k] = 0;
    for (q = 0; q < S; q++) {
      if (adj[k][q]) {
	tmp = busca(q) + 1;
	if (tmp > max_dist[k])
	  max_dist[k] = tmp;
      }
    }
  }
  return max_dist[k];
}

int main(void) {
  int i, a, b;
  
  scanf("%d%d%d", &S, &T, &P);
  for (i=0; i<S; i++)
    scanf("%d", &altura[i]);
  memset(adj, 0, sizeof(adj));
  for (i=0; i<T; i++) {
    scanf("%d%d", &a, &b);
    a--; b--;
    if (altura[a] > altura[b])
      adj[a][b] = 1;
    else if (altura[a] < altura[b])
      adj[b][a] = 1;
  }
  memset(max_dist, -1, sizeof(max_dist));
  printf("%d\n", busca(P-1));
  
  return 0;
}
