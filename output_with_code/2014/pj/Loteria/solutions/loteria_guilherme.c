/* Guilherme A. Pinto, OBI-2014, loteria */

#include <stdio.h>

#define N 6

int num[N];

int main(){
  int count,val,i,j;

  for ( i = 0; i < N; i++ ) scanf("%d",&num[i]);

  count = 0;

  for ( i = 0; i < N; i++ ){
    scanf("%d",&val);
    for ( j = 0; j < N; j++ )
      if ( val == num[j] )
	count++;
  }

  switch( count ){
  case 6:
    printf("sena\n");
    break;
  case 5:
    printf("quina\n");
    break;
  case 4:
    printf("quadra\n");
    break;
  case 3:
    printf("terno\n");
    break;
  default:
    printf("azar\n");
  }

  return 0;
}
