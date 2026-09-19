#include<stdio.h>
#include<strings.h>

int i, n, compr, max, pos, pos_anterior, diferenca;

int main(void) {
  scanf("%d %d", &compr,&n);
  scanf("%d", &pos_anterior);
  // distância do início da fita para a primeira gota
  max=pos_anterior-1;
  // distâncias entre duas gotas consecutivas
  for (i=1; i<n; i++) {
    scanf("%d", &pos);
    diferenca=(pos-pos_anterior)/2;
    if (diferenca>max)
      max=diferenca;
    pos_anterior=pos;
  }
  // distância da última gota para o final da fita
  if (compr-pos_anterior>max)
    max=compr-pos_anterior;
  // imprime o resultado
  printf("%d\n", max);
  return 0;
}
