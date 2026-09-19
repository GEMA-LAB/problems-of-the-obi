/*
  OBI 2025 - Fase 1
  Cafeteria
*/
#include <stdio.h>

int main() {
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);

  // pra ter no minimo a de leite, doses precisam ser no maximo isso
  // (divisao inteira arredonda pra baixo)
  int max_doses = (c - a) / d;

  // pra ter no maximo b de leite, doses precisam ser no minimo isso
  // (soma d - 1 pra divisao inteira arredondar pra cima)
  int min_doses = (c - b + d - 1) / d;

  if (min_doses <= max_doses) {
    printf("S\n");
  } else {
    printf("N\n");
  }
  return 0;
}
