// R. Anido
// OBI2015
// Fita colorida

#include <stdio.h>

#define MAX 10000

int N, fita[MAX+2];

int main(void) {
  int i,x;
  
  scanf("%d\n", &N);
  for (i=1; i<=N; i++)
    scanf("%d", &fita[i]);
  fita[0]=-1;   // usa como baliza
  fita[N+1]=-1; // usa como baliza

  for (x=0; x<9; x++) {
    for (i=1; i<=N; i++) {
      if (fita[i]==-1) {
	if (fita[i-1]==x || fita[i+1]==x)
	  fita[i]=x+1;
      }
    }
  }
  for (i=1; i<=N; i++) {
    if (fita[i]==-1) {
      fita[i]=9;
    }
  }
  // imprime a fita, tomando o cuidado de não imprimir espaço em branco depois do último elemento
  for (i=1; i<N; i++)
    printf("%d ", fita[i]);
  printf("%d\n", fita[N]);

  return 0;
}
