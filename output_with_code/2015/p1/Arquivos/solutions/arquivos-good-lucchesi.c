#include <stdio.h>
#include <stdlib.h>

#define MAX_N (112345)

int x[MAX_N];

int compar(const void *a, const void *b) {
  return *(int *) a - *(int *) b;
}

int main(int argc, char *noargs[]) {
  int n, b, i, j, res;
  scanf("%d %d", &n, &b);
  for (i = 0; i < n; ++i) scanf("%d", &x[i]);
  qsort(x, n, sizeof(int), compar);
  i = 0; j = n-1; res = 0;
  while (i < j) {
    if (x[i] + x[j] <= b) ++i;
    ++res;
    --j;
  }
  if (i == j) ++res;
  printf("%d\n", res);
  return 0;
}
