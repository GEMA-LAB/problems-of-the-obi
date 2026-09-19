#include <stdio.h>

int main(int argc, char *noargs[]) {
  int c, n;
  scanf("%d %d", &c, &n);
  printf("%d\n", c % n);
  return 0;
}
