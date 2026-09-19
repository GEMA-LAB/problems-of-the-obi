// OBI 2023 - Fase 2
// Código - Solução para 100 pontos
// Mateus Bezrutchka
//
#include <cstdio>

char codigo[1100];
int n;

int main() {
  scanf("%d", &n);
  scanf(" %s", codigo);

  int contador = 0;
  char letra_anterior = ' ';

  for (int i = 0; i < n; i++) {
    char letra_atual = codigo[i];
    
    if (letra_atual != letra_anterior) {
      if (contador > 0) {
        // agora que mudou a letra, imprime o codigo pra letra anterior
        printf("%d %c ", contador, letra_anterior);
      }
      letra_anterior = letra_atual;
      contador = 1;
    } else {
      contador++;
    }
  }
  // ainda falta imprimir a ultima letra
  printf("%d %c\n", contador, letra_anterior);
  return 0;
}
