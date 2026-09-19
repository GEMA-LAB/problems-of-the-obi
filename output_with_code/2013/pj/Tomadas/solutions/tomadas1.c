#include <stdio.h>

int main() {
  int i, s=-3, t;
  for (i = 0; i < 4; ++i) {
    scanf("%d", &t);
    s += t;
  }
  printf("%d\n", s);
  return 0;
}
