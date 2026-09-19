#include <stdio.h>
#include <stdlib.h>

#define N (112345)

int adj[N][N];
int d[N];
int rotulo[N];

void dfs(int v, int r) {
  int i, w;
  rotulo[v] = r;
  for (i = 0; i < d[v]; ++i) {
    w = adj[v][i];
    if (rotulo[w] == 0) dfs(w, 3-r);
  }
}

int compar(const void *a, const void *b) {
  return  *((int *) a) - *((int *) b);
}

int main(){
  int n, v, m, i, w;
  
  scanf ("%d", &n);
  for (v = 1; v <= n; ++v) {
    d[v] = 0;
    rotulo[v] = 0;
    scanf("%d", &m);
    for (i = 0; i < m; ++i) {
      scanf("%d",  &w);
      adj[v][d[v]++] = w;
    }
  }

  dfs(1, 1);
  
  for (i = 1; i <= 2; ++i) {
    char *sep = "";
    for (v = 1; v <= n; ++v) {
      if (rotulo[v] == i) {
	printf("%s%d", sep, v);
	sep = " ";
      }
    }
    printf("\n");
  }
  
  return 0;
}
