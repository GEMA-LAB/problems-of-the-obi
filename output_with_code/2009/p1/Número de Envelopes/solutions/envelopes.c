/* Solucao para o problema "Número de Envelopes" da OBI 2009
   por: Igor Ribeiro de Assis */

#include <stdio.h>
#include <string.h> 		/* memset() */

#define MAXK 1010

int qtd[MAXK];

int main() {
  int N, K, menor;
  int i, x;
  
  scanf("%d%d", &N, &K);

  /* conta quantos rótulos de cada tipo Aldo tem */
  memset(qtd, 0, sizeof(qtd));
  for (i = 0; i < N; i++) {
    scanf("%d", &x);
    qtd[x]++;
  }

  /* o máximo de envelopes é igual ao numero de rótulos em menor quantidade */
  menor = qtd[1];
  for (i = 2; i <= K; i++)
    if (qtd[i] < menor)
      menor = qtd[i];

  printf("%d\n", menor);

  return 0;
}
