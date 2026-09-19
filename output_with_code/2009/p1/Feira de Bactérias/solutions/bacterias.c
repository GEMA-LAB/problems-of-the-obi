/* Solucao para o problema "Feira de Bactérias" da OBI 2009
   por: Igor Ribeiro de Assis */

#include <stdio.h>
#include <math.h>

int main() {
  int N, D, C, res, i;
  double bact = 0.0;

  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%d%d", &D, &C);
    /* se A > B então log(A) > log(B) */
    if (bact < (double)C*log(D)) {
      /* log(C^D) == C*log(D) */
      bact = C*log(D);
      res = i;
    }
  }
  
  printf("%d\n", res);

  return 0;
}
