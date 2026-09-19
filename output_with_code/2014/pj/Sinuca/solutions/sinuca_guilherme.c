/* Guilherme A. Pinto, OBI-2014, sinuca */

#include <stdio.h>

#define MAX 64

int bola[MAX],N;

int main(){
  int i,j;
  
  scanf("%d",&N);
  for( i = 0; i < N; i++ ) scanf("%d",&bola[i]);
  
  for( i = N; i > 1; i-- )
    for ( j = 0; j < i-1; j++ )
      bola[j] *= bola[j+1];

  if ( bola[0] == 1 ) printf("preta\n");
  else printf("branca\n");

  return 0;
}
