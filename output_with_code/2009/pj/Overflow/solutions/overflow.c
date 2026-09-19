/* Solucao para o problema "Overflow" da OBI 2009
   por: Igor Ribeiro de Assis */

#include <stdio.h>

int main() {
  int N, P, Q, total;
  char o;

  scanf("%d", &N);
  scanf("%d %c %d", &P, &o, &Q);
  
  if (o == '+')
    total = P + Q;
  else total = P * Q;

  if (total > N)
    printf("OVERFLOW\n");
  else printf("OK\n");

  return 0;
}
