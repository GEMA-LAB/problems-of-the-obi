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

  // as unicas celulas com apenas dois vizinhos sao o inicio e o final do trajeto
  for (i=1; i<=l; i++) {
    for (j=1; j<=c; j++) {
      if (mat[i][j]==0) continue;
      conta=mat[i+1][j]+mat[i-1][j]+mat[i][j+1]+mat[i][j-1];
      if (conta==1 && (i!=a || j!=b)) {
	printf("%d %d\n",i,j);
	return 0;
      }
    }
  }
}
