// OBI2024 - Fase 1
// Ogro

#include "stdio.h"

int main() {

  int e, d, res;

  scanf("%d%d", &e, &d);

  if (e > d) {
    res = e + d;
  }
  else {
    res = 2 * (d - e);
  }
  
  printf("%d\n", res);
  
}
