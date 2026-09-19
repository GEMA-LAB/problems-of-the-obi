// Sequência secreta
// OBI2019
// R. Anido

#include<stdio.h>

int n; 
int atual; // último valor marcado na sequência
int total; // total de valores marcados

int main(void) {
  int i, x;

  scanf("%d", &n);
  atual = -1;  //inicializa com um número diferente dos valores 1 e 2
  total = 0;  // total de números marcados

  for (i=0; i<n; i++) {
    scanf("%d", &x);
    // cada vez que encontra um número diferente do 
    // último marcado, marca esse novo número
    if (atual != x) {
      atual = x;
      total += 1;
    }
  } 
  printf("%d\n",total);
  return(0);
}
