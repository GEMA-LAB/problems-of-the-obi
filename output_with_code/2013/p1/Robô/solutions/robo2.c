// OBI2013
// robô

#include <stdio.h>

#define MAXL 1000
#define MAXC 1000
int mat[MAXL+2][MAXC+2];

int main(void) {
  int l,c,a,b;
  int i,j,conta;

  scanf("%d %d", &l,&c);
  scanf("%d %d", &a,&b);
  // faz uma moldura de zeros ao redor do chao
  for (i=0; i<=l+1; i++) {
    mat[i][0]=0;
    mat[i][c+1]=0;
  }
  for (j=0; j<=c+1; j++) {
    mat[0][j]=0;
    mat[l+1][j]=0;
  }

  for (i=1; i<=l; i++)
    for (j=1; j<=c; j++)
      scanf("%d",&mat[i][j]);

  while (1) {
    mat[a][b]=0;
    if (mat[a+1][b]==1)
      a=a+1;
    else if (mat[a-1][b]==1)
      a=a-1;
    else if (mat[a][b+1]==1)
      b=b+1;
    else if (mat[a][b-1]==1)
      b=b-1;
    else // final do percurso
      break;
  }
  printf("%d %d\n",a,b);
  return 0;
}
