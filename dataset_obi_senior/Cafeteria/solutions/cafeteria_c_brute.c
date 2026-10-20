/*
  OBI 2025 - Fase 1
  Cafeteria
*/
#include <stdio.h>

int main() {
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  int possivel = 0;

  // testa todas as quantidades de doses
  for (int doses = 1; doses * d <= c; doses++) {
    int leite = c - doses * d;
    if (a <= leite && leite <= b) {
      possivel = 1;
    }
  }

  if (possivel) {
    printf("S\n");
  } else {
    printf("N\n");
  }
  return 0;
}
