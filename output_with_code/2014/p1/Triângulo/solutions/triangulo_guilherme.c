/* Guilherme A. Pinto - OBI 2014 - Triangulo */

#include <stdio.h>

int triangulo( int p, int q, int r  ){
  if ( p < q+r && q < p+r && r < p+q ) return 1;
  return 0;
}


int main() {
  int a,b,c,d;
  
  scanf("%d%d%d%d",&a,&b,&c,&d);

  if ( triangulo( a, b, c ) ||
       triangulo( a, b, d ) ||
       triangulo( a, c, d ) ||
       triangulo( b, c, d ) ) printf("S\n");
  else printf("N\n");

  return 0;
}
