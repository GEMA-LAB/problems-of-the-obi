// OBI2021 - Fase 2
// Potência

#include <cstdio>

using namespace std;

int n, t;
long resposta = 0;

int main(void) {
  int potencia, p, base;
  
  scanf("%d", &n);

  for (int i=0; i<n; i++) {
    scanf("%d", &t);
    p = t % 10;
    base = t / 10;

    potencia = 1;
    for (int j=0; j<p; j++)
      potencia *= base;

    resposta += potencia;
  }
  printf("%ld\n", resposta);

  return 0;
}
