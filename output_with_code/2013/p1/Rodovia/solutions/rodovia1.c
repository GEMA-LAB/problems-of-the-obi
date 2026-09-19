#include <stdio.h>

#define MAX_N (11234)

int in[MAX_N + 1];
int out[MAX_N + 1];
int vis[MAX_N + 1];
int adj[MAX_N + 1];

int main() {
  int n, i, v, w, n_vis;
  char res = 'S';

  scanf("%d", &n);
  for (v = 1; v <= n; ++v) {
    in[v] = 0;
    out[v] = 0;
    vis[v] = 0;
  }

  for (i = 1; i <= n; ++i) {
    scanf("%d %d", &v, &w);
    adj[v] = w;
    ++out[v];
    ++in[w];
  }

  for (v = 1; v <= n; ++v) {
    if ((in[v] != 1) || (out[v] != 1)) {
      res = 'N';
      break;
    }
  }

  v = 1;
  n_vis = 0;
  while (vis[v] == 0) {
    vis[v] = 1;
    ++n_vis;
    v = adj[v];
  } 
  if (n_vis != n) res = 'N';
  printf ("%c\n", res);
  return 0;
}
  
