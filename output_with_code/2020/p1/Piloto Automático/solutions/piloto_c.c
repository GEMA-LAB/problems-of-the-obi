/* OBI-2020, piloto, Guilherme A. Pinto */

#include "stdio.h"

int main(){

  int A, B, C;

  scanf("%d%d%d",&A,&B,&C);

  int distAB = B-A;
  int distBC = C-B;

  if ( distAB < distBC ){
    printf("1\n");
  } else {
    if ( distAB > distBC ){
      printf("-1\n");
    } else {
      printf("0\n");
    }
  }

  return 0;
}