/* Guilherme A. Pinto - OBI 2014 - Gangorra */

#include <stdio.h>

int main() {
  int C1,P1,C2,P2;
  
  scanf("%d%d%d%d",&C1,&P1,&C2,&P2);
 
  if ( C1*P1 == C2*P2 ) printf("0\n");
  else if ( C1*P1 > C2*P2 ) printf("-1\n");
  else printf("1\n");

  return 0;
}
