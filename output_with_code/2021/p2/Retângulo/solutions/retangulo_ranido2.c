// r. anido
// retangulo
// OBI2021 - fase 2

#include<stdio.h>
#define MAXN 100000

int n;
int trees[MAXN];

int main(void) {
  int arc_sum=0, p=0, q=0, np=0, i;

  scanf("%d", &n);
  for (i=0; i< n; i++) {
    scanf("%d", &trees[i]);
    arc_sum = arc_sum - trees[i];
  }
  // procura por dois pares de pontos diametricalmente opostos
  while (q != n && np < 2) {
    if (arc_sum > 0) {  //advance p
      arc_sum = arc_sum - 2*trees[p];
      p++;
    }
    else if (arc_sum < 0) { // advança q
      arc_sum = arc_sum + 2*trees[q];
      q++;
    }
    else {  // avança p e q
      arc_sum = arc_sum - 2*trees[p] + 2*trees[q];
      p++; q++; np++;
    }
  }
  if (np >= 2)
    printf("S\n");
  else
    printf("N\n");
}
