/* Guilherme A. Pinto, OBI 2014, quadrado */

#include <stdio.h>

#define MAXN 50

int q[MAXN][MAXN];
int li[MAXN],cj[MAXN];
int N,M;

int main(){
  int i,j,k,original,novo;

  scanf("%d",&N);
  for( k = 0; k < N; k++ )
      li[k] = cj[k] = 0;
  for( i = 0; i < N; i++ )
    for( j = 0; j < N; j++ ){
      scanf("%d",&q[i][j]);
      li[i] += q[i][j];
      cj[j] += q[i][j];
    }

  M = li[0];
  if ( li[0] != li[1] && li[1] == li[2] ) M = li[1];

  for( k = 0; k < N; k++ )
    if ( li[k] != M ) i = k;
  for( k = 0; k < N; k++ )
    if ( cj[k] != M ) j = k;

  novo = q[i][j];

  li[i] -= novo;
  original = M-li[i];

  printf("%d %d\n",original,novo);

  return 0;
}
