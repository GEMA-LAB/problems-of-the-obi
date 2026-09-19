/* Guilherme A. Pinto - OBI 2014 - Triangulo */

#include <stdio.h>

int main() {
  int a,b,c,d;
  
  scanf("%d%d%d%d",&a,&b,&c,&d);

  /* a b c */
  if ( a < b + c && b < a + c && c < a + b ){
    printf("S\n");
    return 0;
  }

  /* a b d */
  if ( a < b + d && b < a + d && d < a + b ){
    printf("S\n");
    return 0;
  }

  /* a c d */
  if ( a < c + d && c < a + d && d < a + c ){
    printf("S\n");
    return 0;
  }

  /* b c d */
  if ( b < c + d && c < b + d && d < b + c ){
    printf("S\n");
    return 0;
  }

  printf("N\n");
  return 0;
}
