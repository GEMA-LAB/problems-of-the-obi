// OBI2021 - Fase 1
// Torneio de Tenis

#include <cstdio>

using namespace std;


int vitorias = 0;
char resultado;

int main(void) {
  for (int i=0; i<6; i++) {
    scanf("%c\n", &resultado);
    if (resultado == 'V')
      vitorias++;
  }
  
  if (vitorias == 0)
    printf("-1\n");
  else if(vitorias <= 2)
    printf("3\n");
  else if(vitorias <= 4)
    printf("2\n");
  else
    printf("1\n");

  return 0;
}
