#include <stdio.h>

#define min(x,y) (x <= y ? x : y)

int main() {
  int n, s, min_s, i, d;
  scanf ("%d %d", &n, &s);
  min_s = s;
  for (i = 0; i < n; ++i) {
    scanf("%d", &d);
    s += d;
    min_s = min(min_s, s);
  }
  printf ("%d\n", min_s);
  return 0;
}
