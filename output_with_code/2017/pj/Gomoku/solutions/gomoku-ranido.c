#include <stdio.h>

#define N 15
int tabuleiro[N+2][N+2];
int direcao[4][2]={
  {1,0},
  {0,1},
  {1,1},
  {1,-1}};

int main(void) {
  int i,j,x,y,dir;
  int cor,conta,res;
  int xh,yh;

  // vamos usar uma moldura de zeros
  for(i=0;i<N+2;i++) {
    tabuleiro[0][i]=0;
    tabuleiro[i][N+1]=0;
    tabuleiro[i][0]=0;
    tabuleiro[N+1][i]=0;
  }
  // lê entrada
  for(i=1;i<=N;i++)
    for(j=1;j<=N;j++)
      scanf("%d",&tabuleiro[i][j]);

  // procura cinco pedras de mesma cor nas quatro direções
  res=0;
  for(dir=0; dir<4; dir++)
    for(y=1; y<=15; y++)
      for(x=1; x<=15; x++)
	if ((cor=tabuleiro[x][y]) &&
	    tabuleiro[x][y] != tabuleiro[x-direcao[dir][0]][y-direcao[dir][1]]) {
	  conta=0;
	  xh=x, yh=y;
	  while(tabuleiro[xh][yh]==cor) {
	    xh+=direcao[dir][0];
	    yh+=direcao[dir][1];
	    conta++;
	  }
	  if (conta==5)
	    res=cor;
	}

  // imprime o resultado
  printf("%d\n",res);
  return 0;
}
