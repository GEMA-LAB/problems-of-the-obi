// OBI2020
// musica

#include <cstdio>
#include <cstring>
#define MAX 100000

int favorita[MAX];
int visitado[MAX];

int main(void){
  int n, m, tocando; 
  int a, b;
  int trocas = 0;

  memset(favorita, -1, sizeof(favorita));
  memset(visitado, 0, sizeof(visitado));
  scanf ("%d%d%d", &n, &m, &tocando);
  tocando--;
  for (int i=0; i<n; i++){
    scanf("%d%d", &a, &b);
    a--; b--;
    if (favorita[b] == -1)
      favorita[b] = a;
  }

  while(visitado[tocando] == 0 && favorita[tocando] != -1){
    trocas++;
    visitado[tocando] = 1;
    tocando = favorita[tocando];
  }

  if (visitado[tocando] == 0)
    printf("%d\n", trocas);
  else
    printf("-1\n");

  return 0;
}
