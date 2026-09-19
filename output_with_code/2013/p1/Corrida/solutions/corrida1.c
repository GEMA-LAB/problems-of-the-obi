#include <stdio.h>

int main() {
  int n[2], d, v, i;
  double t[2], hum = 1;
  for (i = 0; i < 2; ++i) {
    scanf ("%d %d %d", &n[i], &d, &v);
    t[i] = hum * d / v;
  }
  printf("%d\n",  t[0] < t[1] ? n[0] : n[1]);
  return 0;
}
