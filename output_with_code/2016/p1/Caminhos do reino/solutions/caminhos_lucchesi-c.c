#include <stdio.h>
#include <string.h>

#define N (112345)

#define min(x,y) (x <= y ? x : y)
#define max(x,y) (x >= y ? x : y)

//
// in_d[v] = in_degree[v]
//
// d2cycle[v] = distance from v to nearest vertex in cycle (0 if v in
// cycle) 
//
// or_cycle = a vertex in the cycle
//
// d_from_or_cycle[v] = distance from or_cycle to v, if v in cycle
//
// len_cycle = number of vertices in the cycle
//
// end_per[v] = end of peripheral path containing v (v itself if v in
// cycle)
//

int f[N], in_d[N], d2cycle[N], or_cycle, d_from_or_cycle[N], len_cycle, end_per[N];

void dfs(int v) {
  if (d2cycle[v] == 0) return;
  dfs(f[v]);
  d2cycle[v] = 1 + d2cycle[f[v]];
  end_per[v] = end_per[f[v]];
}

int main() {
  int n, q, i, v, w;
  scanf("%d", &n);
  for (v = 1; v <= n; ++v) {
    in_d[v] = 0;
    d2cycle[v] = n;
  }

  // lê input e calcula in_d
  for (v = 1; v <= n; ++v) {
    scanf("%d", &f[v]);
    ++in_d[f[v]];
    /* printf("f[%d] = %d\n", v, f[v]); */
  }
  
  // find cycle
  for (v = 1; v <= n; ++v) {
    if (in_d[v] > 1) {
      or_cycle = v;
      break;
    }
  }
  /* printf("cycle ="); */
  len_cycle = 0;
  v = or_cycle;
  do {
    /* printf(" %d", v); */
    d2cycle[v] = 0;
    d_from_or_cycle[v] = len_cycle++;
    end_per[v] = v;
    v = f[v];
  } while (v != or_cycle);
  /* printf("\nlen_cycle = %d\n", len_cycle); */
  // peripheral paths: end of peripheral path and distance to cycle
  for (v = 1; v <= n; ++v) {
    if (in_d[v] == 0) dfs(v);
  }

  /* for (v = 1; v <= n; ++v) { */
  /*   printf("d2cycle[%d] = %d end_per[%d] = %d\n", v, d2cycle[v], v, end_per[v]); */
  /* } */
  
  scanf("%d", &q);
  for (i = 0; i < q; ++i) {
    int res, d_end_v2end_w;
    scanf("%d %d", &v, &w);
    /* printf("%d -> %d: ", v, w); */
    if (d2cycle[v] < d2cycle[w]) {
      int vv = v;
      v = w;
      w = vv;
    }
    if (end_per[v] == end_per[w]) res = d2cycle[v] - d2cycle[w];
    else{
      d_end_v2end_w = d_from_or_cycle[end_per[w]] - d_from_or_cycle[end_per[v]];
      if (d_end_v2end_w < 0) d_end_v2end_w += len_cycle;
      res = min(d2cycle[v] + d_end_v2end_w, max(d2cycle[v], d2cycle[w] + len_cycle - d_end_v2end_w));
      /* printf("d2cycle[%d] = %d d2cycle[%d] = %d d_end_v2end_w = %d d_end_w2end_v = %d ", */
      /* 	     v, d2cycle[v], w, d2cycle[w], d_end_v2end_w, len_cycle - d_end_v2end_w); */
    }
    printf("%d\n", res);
  }
  return 0;
}
