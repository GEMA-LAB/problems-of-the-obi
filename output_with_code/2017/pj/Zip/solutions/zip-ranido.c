#include <stdio.h>

int l1,l2,c1,c2;

int main(void) {
  int lp,cp;

  scanf("%d%d%d%d",&l1,&l2,&c1,&c2);
  if (l1==l2)
    lp=2*(l1+l2);
  else if (l1==l2+1||l1+1==l2)
    lp=3*(l1+l2);
  else
    lp=l1+l2;
  if (c1==c2)
    cp=2*(c1+c2);
  else if (c1==c2+1||c1+1==c2)
    cp=3*(c1+c2);
  else
    cp=c1+c2;
  if (lp>cp)
    printf("Lia\n");
  else if (lp<cp)
    printf("Carolina\n");
  else
    printf("empate\n");
}
