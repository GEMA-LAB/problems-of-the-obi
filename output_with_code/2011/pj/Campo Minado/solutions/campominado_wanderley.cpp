#include <stdio.h>

#define MAX 50

int main () {
  int R[MAX], N, v, i;

  for (i = 0; i < MAX; i++) {
    R[i] = 0;
  }

  scanf ("%d", &N);
  for (i = 0; i < N; i++) {
    scanf ("%d", &v);
    if (i > 0)   { R[i-1] += v; }
    R[i] += v;
    if (i+1 < N) { R[i+1] += v; }
  }
  for (i = 0; i < N; i++) {
    printf ("%d\n", R[i]);
  }

  return 0;
}
