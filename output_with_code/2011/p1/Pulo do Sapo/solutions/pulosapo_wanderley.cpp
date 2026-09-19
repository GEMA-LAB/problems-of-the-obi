#include <stdio.h>

#define MAX 100

int main () {
  int N, M, p, d, resp[MAX], i, j;

  for (i = 0; i < MAX; i++) {
    resp[i] = 0;
  }

  scanf ("%d %d", &N, &M);
  for (i = 0; i < M; i++) {
    scanf ("%d %d", &p, &d);
    p--;

    for (j = p; j < N; j += d) {
      resp[j] = 1;
    }
    for (j = p; j >= 0; j -= d) {
      resp[j] = 1;
    }
  }

  for (i = 0; i < N; i++) {
    printf ("%d\n", resp[i]);
  }

  return 0;
}
