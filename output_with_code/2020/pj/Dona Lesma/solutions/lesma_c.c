// OBI2020 - Fase 2
// dona lesma

#include <stdio.h>

int main(void) {
  int a, s, d;
  
  scanf("%d%d%d", &a, &s, &d);
  printf("%d\n", (a-d-1)/(s-d)+1);

  return 0;
}
