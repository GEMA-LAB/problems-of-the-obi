// OBI 2023 - Fase 2
// Grupos - Solução linear com vetor de marcação
// Mateus Bezrutchka
// 
#include <cstdio>

const int MAXN = 1000100;
int grupo[MAXN]; // indice do grupo do estudante
int juntos[MAXN][2]; // pares de estudantes que querem estar juntos
int separados[MAXN][2]; // pares de estudantes que querem estar separados
int E, M, D;

int main() {
  int a, b, c;

  scanf("%d %d %d", &E, &M, &D);
  for (int i = 1; i <= M; i++) {
    scanf("%d %d", &juntos[i][0], &juntos[i][1]);
  }
  for (int i = 1; i <= D; i++) {
    scanf("%d %d", &separados[i][0], &separados[i][1]);
  }
  for (int i = 1; i <= E / 3; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    grupo[a] = grupo[b] = grupo[c] = i;
  }

  int num_violacoes = 0;
  for (int i = 1; i <= M; i++) {
    a = juntos[i][0]; b = juntos[i][1];
    if (grupo[a] != grupo[b]) {
      num_violacoes++;
    }
  }
  for (int i = 1; i <= D; i++) {
    a = separados[i][0]; b = separados[i][1];
    if (grupo[a] == grupo[b]) {
      num_violacoes++;
    }
  }

  printf("%d\n", num_violacoes);
  return 0;
}
