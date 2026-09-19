/* Guilherme A. Pinto, OBI-2014, bolinha */

#include <stdio.h>

#define MAXN 100

typedef struct cell_ { int v,c; } cell;

cell m[MAXN+1][MAXN+1];
int N,I,J,res;
int d[5] = {0,1,0,-1,0};

void passaBolinha( int i, int j ){
  int k,a,b;

  /* levanta a bandeira */
  m[i][j].c = 1; 
  res++;

  /* quatro vezes a mesma acao */
  for( k = 0; k < 4; k++ ){
    /* vira-se 90 graus */
    a = i+d[k]; b = j+d[k+1];
    /* dentro do quadrado? */
    if ( a >= 1 && a <= N && b >= 1 && b <= N )
      /* número maior e bandeira abaixada? */
      if ( (m[a][b].v >= m[i][j].v) && (m[a][b].c == 0) )
	passaBolinha( a, b );
  }
}

int main(){
  int i,j;

  scanf("%d%d%d",&N,&I,&J);

  for( i = 1; i <= N; i++ )
    for( j = 1; j <= N; j++ ){
      scanf("%d",&m[i][j].v);
      m[i][j].c = 0;
    }

  res = 0;
  passaBolinha( I, J );

  printf("%d\n",res);
  return 0;
}
