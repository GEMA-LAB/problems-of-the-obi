/* Guilherme A. Pinto - OBI 2014 - Semente */

#include <stdio.h>
#include <math.h>

#define MAXR 1000

int d[MAXR],F,R;

int main() {
  int i,ans;
  float f;
  
  scanf("%d%d",&F,&R);
  for ( i = 0; i < R; i++ )
    scanf("%d",&d[i]);
  
  ans = (d[0]-1)>(F-d[R-1])?(d[0]-1):(F-d[R-1]);
  
  for ( i = 1; i < R; i++ ){
    f = floor((float)(d[i]-d[i-1])/(float)2);
    if ( f > ans ) ans = f;
  }

  printf("%d\n",ans);
  return 0;
}
