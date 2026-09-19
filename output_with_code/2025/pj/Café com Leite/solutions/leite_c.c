/*
  OBI 2025 - Fase 1
  Cafe com Leite
*/
#include <stdio.h>

int main() {
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);

  if (a <= c - d && c - d <= b) {
    printf("S\n");
  } else {
    printf("N\n");
  }
  return 0;
}
