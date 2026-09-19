/* Guilherme A. Pinto, OBI-2014, sinuca */

#include <stdio.h>

typedef unsigned long long u64;

int main(){
  u64 b;
  int N,v,i;
  
  scanf("%d",&N);
  for( b = 0, i = 0; i < N; i++ ){
    scanf("%d",&v);
    b <<= 1; if ( v == -1 ) b++;
  }
  
  for( i = N; i > 1; i-- ) b ^= b >> 1;

  if ( b & 1 ) printf("branca\n");
  else printf("preta\n");

  return 0;
}
