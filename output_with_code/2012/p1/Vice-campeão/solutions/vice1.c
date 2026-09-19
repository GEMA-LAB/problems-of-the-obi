#include <stdio.h>

int main(int argc, char *noargs[]) {
  int a, b, c, res;
  scanf("%d %d %d", &a, &b, &c);
  if (((a < b) && (b < c)) || ((c < b) && (b < a))) res = b;
  else if (((b < a) && (a < c)) || ((c < a) && (a < b))) res = a;
  else res = c;
  printf("%d\n", res);
  return 0;
}
