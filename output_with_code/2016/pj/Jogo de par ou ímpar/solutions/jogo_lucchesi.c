#include <stdio.h>

int main(int argc, char *noargs[]) {
  int P, D1, D2, V;
  scanf("%d %d %d", &P, &D1, &D2);
  if ((D1 + D2) % 2 == P) V = 0;
  else V = 1;
  printf("%d\n", V);
  return 0;
}
