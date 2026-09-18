// OBI2021 - Fase 2
// Cálculo rápido

#include <cstdio>

using namespace std;


int s, a, b;
int resposta = 0;

int main(void) {
  scanf("%d%d%d", &s, &a, &b);

  // para cada número no intervalo, soma os dígitos
  // e compara com s
  for (int i=a; i<=b; i++) {
    int soma = 0, num = i;
    while (num > 0) {
      soma += num % 10;
      num = num / 10;
    }
    if (soma == s)
      resposta++;
  }
  printf("%d\n", resposta);

  return 0;
}
