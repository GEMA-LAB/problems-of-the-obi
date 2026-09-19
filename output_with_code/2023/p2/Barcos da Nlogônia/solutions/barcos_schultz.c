/*
 * +------------------------------------------+
 * | Solution to problem "caminhao", by       |
 * | Luís Fernando Schultz Xavier da Silveira |
 * +------------------------------------------+
 * | This code is under the GPLv3 license.    |
 * +------------------------------------------+
 *
 *
 * Problem description
 * ===================
 *
 * A weighted undirected graph is given along with several queries.
 * Each query requires finding a path that maximizes the weight of
 * the minimum weight edge in it.
 *
 * The graph has n vertices and m edges, and S queries are given.
 * The solution described here runs in O((n+m+S) log n) time
 * and demands O(n log n) space, and the limits of this problem were
 * selected having these complexities in mind.
 *
 * 
 * Idea of the solution
 * ====================
 *
 * "There is always such a maximizing path along the edges of any
 * maximum spanning tree" is a proper way of summing it up in one
 * sentence. This statement is proven correct in the next section
 * and, for the remainder of this section, it is assumed true.
 *
 * It is therefore sufficient to consider only edges in this maximum
 * spanning tree, discarding the rest. In a tree, there is only one
 * path between any pair of nodes, and as such it is enough to
 * compute the weight of the minimum weight edge in this path.
 *
 * To compute this weight efficiently, we use the concept of a least
 * common ancestor. First we choose an arbitrary root for the tree and
 * treat it as a rooted tree with the chosen root. Each node then has
 * its depth determined. The least common ancestor of two nodes u and v
 * is the ancestor node of both u and v in the tree that has minimum
 * depth.
 *
 * Using a dynamic programming algorithm described further, we can
 * find the least commong ancestor of two nodes u and v as well as the
 * minimum weight edge in the paths from u and v to this ancestor,
 * all this in O(log n) time.
 *
 *
 * Proof of correctness of the idea
 * ================================
 *
 * Consider a maximum spanning tree T for the graph and fix any
 * two distinct nodes u and v from it. Let e0 be an edge of minimum
 * weight among all edges in the path from u to v in T and let w0 be
 * that weight. For the purposes of a proof by contradiction, suppose
 * there exists a path P from u to v, not necessarily
 * using only edges from T, whose minimum weight edge has weight
 * w1 > w0.
 *
 * Removing the edge e0 from T leaves us with a spanning forest
 * T\{e0} consisting of two connected components, one containing u
 * and the other containing v. The path P, however, connects u and v,
 * and thus there must exist at least one edge e1 which has extremes
 * in both connected components. Adding the edge e1 to the forest
 * gives us a spanning tree (T\{e0})U{e1} of weight at least
 *   weight(T)-w0+w1,
 * which is greater than the weight of T, a contradiction.
 * 
 * Thus our claim is proven and out of our way.
 *
 *
 * Computing maximum weight spanning trees
 * =======================================
 *
 * There are at least a couple of different ways to do this.
 * One of the would be negating the weight of all edges in the graph
 * and obtaining a minimum spanning tree, which is a maximum
 * weight spanning tree in the original graph.
 *
 * It is desirable to use Prim's algorithm, which, using binary
 * heaps, yields a time complexity of O((m+n) log n) using only
 * O(n) extra space.
 *
 * This algorithm can also be modified by giving it a comparison
 * function of the weights of the edges that considers an edge weight
 * less than another when actually it is greater, giving a simpler
 * implementation. The proof this can be done is left as an exercise
 * for the reader.
 *
 * ============= THE REST IS YET TO BE DONE =================
 */

#include <string.h>
#include <limits.h>
#include <stdio.h>

typedef struct edge {
  struct edge* next;
  int v;
  int w;
} edge_t;

typedef struct {
  int* pos;
  int u;
  int key;
} heap_node_t;

typedef struct {
  int pi;
  int min;
} dp_t;

static void heap_increase_key (heap_node_t* H, int i) {
  heap_node_t node = H[i];
  while (i != 0) {
    int j = (i-1)>>1;
    if (H[j].key >= node.key)
      break;
    H[i] = H[j];
    *H[i].pos = i;
    i = j;
  }
  H[i] = node;
  *H[i].pos = i;
}

static void heap_decrease_key (heap_node_t* H, int n, int i) {
  heap_node_t node = H[i];
  int j;
  for (;;) {
    j = (i+1)<<1;
    if (j >= n)
      break;
    if (H[j-1].key > H[j].key)
      --j;
    if (H[j].key <= node.key)
      goto put_node;
    H[i] = H[j];
    *H[i].pos = i;
    i = j;
  }
  if (j == n) {
    --j;
    if (H[j].key > node.key) {
      H[i] = H[j];
      *H[i].pos = i;
      i = j;
    }
  }
put_node:
  H[i] = node;
  *H[i].pos = i;
}

static void
mst
 (dp_t* row,
  int* depth,
  const edge_t*const* G,
  int* D,
  heap_node_t* H,
  int* P,
  int n)
{
  memset (depth, -1, n*sizeof(depth[0]));
  memset (D, 0, n*sizeof(D[0]));
  row[0].pi = 0;
  H[0].u = 0;
  H[0].key = INT_MAX;
  H[0].pos = &P[0];
  P[0] = 0;
  int h = 1;
  while (h != 0) {
    int u = H[0].u;
    row[u].min = H[0].key;
    depth[u] = depth[row[u].pi]+1;
    H[0] = H[--h];
    *H[0].pos = 0;
    heap_decrease_key (H, h, 0);
    for (const edge_t* p = G[u]; p != NULL; p = p->next) {
      int v = p->v;
      int w = p->w;
      if (depth[v] < 0 && w > D[v]) {
        if (D[v] == 0) {
          H[h].u = v;
          H[h].pos = &P[v];
          P[v] = h;
          ++h;
        }
        D[v] = w;
        int i = P[v];
        H[i].key = w;
        heap_increase_key (H, i);
        row[v].pi = u;
      }
    }
  }
}

#define NMAX 100000
#define MMAX 100000
#define KMAX     20

static edge_t      E     [MMAX<<1];
static edge_t*     G     [NMAX];
static int         D     [NMAX];
static heap_node_t H     [NMAX];
static int         P     [NMAX];
static int         depth [NMAX];
static dp_t        DP    [KMAX][NMAX];

int main (void) {
  int n, m, S;
  while (scanf ("%d%d", &n, &m) == 2) {
    memset (G, 0, n*sizeof(G[0]));
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      scanf ("%d%d%d", &u, &v, &w);
      --u;
      --v;
      int e = i<<1;
      E[e].v = v;
      E[e].w = w;
      E[e].next = G[u];
      G[u] = &E[e];
      e^= 1;
      E[e].v = u;
      E[e].w = w;
      E[e].next = G[v];
      G[v] = &E[e];
    }
    int k = 1;
    while ((1<<k) < n)
      ++k;
    mst (DP[0], depth, (const edge_t*const*)G, D, H, P, n);
    for (int i = 1; i < k; ++i)
      for (int u = 0; u < n; ++u) {
        int v = DP[i-1][u].pi;
        DP[i][u].pi = DP[i-1][v].pi;
        int x = DP[i-1][u].min;
        int y = DP[i-1][v].min;
        DP[i][u].min = x < y ? x : y;
      }
    scanf ("%d", &S);
    while (S--) {
      int u, v;
      scanf ("%d%d", &u, &v);
      --u;
      --v;
      int min = INT_MAX;
      if (depth[u] > depth[v]) {
        int t = u;
        u = v;
        v = t;
      }
      for (int i = k-1; i >= 0; --i)
        if ((1<<i) <= depth[v]-depth[u]) {
          int x = DP[i][v].min;
          if (x < min)
            min = x;
          v = DP[i][v].pi;
        }
      if (u == v)
        goto output;
      for (int i = k-1; i >= 0; --i) {
        int u1 = DP[i][u].pi;
        int v1 = DP[i][v].pi;
        if (u1 != v1) {
          int x = DP[i][u].min;
          if (x < min)
            min = x;
          int y = DP[i][v].min;
          if (y < min)
            min = y;
          u = u1;
          v = v1;
        }
      }
      int x = DP[0][u].min;
      if (x < min)
        min = x;
      int y = DP[0][v].min;
      if (y < min)
        min = y;
output:
      printf ("%d\n", min);
    }
  }
  return 0;
}


