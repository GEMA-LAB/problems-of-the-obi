// r. anido
// problema tabuleiro, OBI2017

#include <stdio.h>

#define MAX 100

int n;
int tab[MAX][MAX];


int main(void) {
  int i,j;
  
  scanf("%d",&n);              // lê valor de N
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      scanf("%d", &tab[i][j]);        // lê os valores do tabuleiro

  for (i=1; i<n; i++)         // agora percorre o tabuleiro, verificando a condição
    for (j=1; j<n; j++)
      if (tab[i-1][j-1]+tab[i-1][j]+tab[i][j-1]>=2) 
        tab[i][j]=0;
      else
        tab[i][j]=1;

  printf("%d\n",tab[n-1][n-1]);   // imprime a resposta
  return 0;
}
