// Guilherme A. Pinto, OBI-2016, medalhas

#include <bits/stdc++.h>

int main() {
  int T1,T2,T3;
  int ouro,prata,bronze;

  scanf("%d",&T1);
  scanf("%d",&T2);
  scanf("%d",&T3);

  if ( T1 < T2 && T2 < T3 ) { ouro = 1; prata = 2; bronze = 3; }
  if ( T1 < T3 && T3 < T2 ) { ouro = 1; prata = 3; bronze = 2; }
  if ( T2 < T1 && T1 < T3 ) { ouro = 2; prata = 1; bronze = 3; }
  if ( T2 < T3 && T3 < T1 ) { ouro = 2; prata = 3; bronze = 1; }
  if ( T3 < T1 && T1 < T2 ) { ouro = 3; prata = 1; bronze = 2; }
  if ( T3 < T2 && T2 < T1 ) { ouro = 3; prata = 2; bronze = 1; }

  printf("%d\n",ouro);
  printf("%d\n",prata);
  printf("%d\n",bronze);
  
  return 0;
}
