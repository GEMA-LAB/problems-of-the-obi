#include <stdio.h>

#define MAXID 100000
#define MAXFILA 50000

int removido[MAXID+1];
int fila[MAXFILA];
int M,N;

int main(void) {
  int i, j, r, primeiro;
  
  // le a fila inicial
  scanf("%d",&N);
  for (i=0;i<N;i++)
    scanf("%d",&fila[i]);

  // marca todos os IDs como não removidos
  for (i=0;i<MAXID;i++)
    removido[i]=0;

  // le os removidos e marca o ID correspondente
  scanf("%d",&M);
  for (i=0;i<M;i++) {
    scanf("%d",&r);
    removido[r]=1;
  }

  // imprime a fila, tomando o cuidado de imprimir brancos apenas entre dois valores
  // apenas elementos para os quais removido é iguol a zero são impressos
  primeiro=1;
  for (i=0;i<N;i++) {
    if (removido[fila[i]]==1)
      continue;
    if (primeiro==1) {
      printf("%d",fila[i]);
      primeiro=0;
    }
    else
      printf(" %d",fila[i]);
  }
  printf("\n");
  return 0;
}
