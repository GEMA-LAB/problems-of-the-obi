// r. anido
// retangulo
// OBI2021 - Fase 2

#include<stdio.h>
#define MAXN 100000

int n;
int arvores[MAXN];

int main(void) {
  int arc_sum=0, half_circ, p=0, q=0, np=0, i;

  scanf("%d", &n);
  for (i=0; i< n; i++) {
    scanf("%d", &arvores[i]);
    arc_sum = arc_sum + arvores[i];
  }
  if (arc_sum % 2 == 1) {
    printf("N\n");
    return 0;
  }
  half_circ = arc_sum/2;
  arc_sum = 0;
  // procura por dois pares de pontos diametricalmente opostos
  while (q != n && np < 2) {
    if (arc_sum < half_circ) {  //avança q
      arc_sum = arc_sum + arvores[q];
      q++;
    }
    else if (arc_sum > half_circ) { // avança p
      arc_sum = arc_sum - arvores[p];
      p++;
    }
    else {  // avança p e q
      arc_sum = arc_sum - arvores[p] + arvores[q];
      p++; q++; 
      //if (arc_sum > 0) 
	np++;
    }
  }
  if (np >= 2)
    printf("S\n");
  else
    printf("N\n");
  return 0;
}
