#include <stdio.h>

int main(void) {
  int n, a, i, soma;
  
  scanf("%d", &n);
  soma = 0;
  for (i=1; i<=n; i++) {
    scanf("%d", &a);
    soma += a;
    if (soma>=1000000)
      break;
  }
  printf("%d\n", i);
}
