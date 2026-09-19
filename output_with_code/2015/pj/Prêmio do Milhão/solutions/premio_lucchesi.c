#include <stdio.h>

int main(int argc, char *noargs[]) {
  int n, p;
  int res = 0, soma = 0;
  
  scanf("%d", &n);

  while (n-- > 0) {
    scanf("%d", &p);
    if (soma >= 1000000) continue;
    soma += p;
    ++res;
  }
  printf("%d\n", res);
  return 0;
}
