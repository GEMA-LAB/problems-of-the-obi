// OBI 2023 - Fase 2
// Prefixo - Solução
// Mateus Bezrutchka
//
#include <cstdio>
#include <algorithm>
using namespace std;

char A[1100];
char B[1100];
int n, m;

int main() {
  scanf("%d", &n);
  scanf(" %s", A);

  scanf("%d", &m);
  scanf(" %s", B);

  for (int i = 0; i < min(n, m); i++) {
    if (A[i] != B[i]) {
      printf("%d\n", i);
      return 0;
    }
  }
  printf("%d\n", min(n, m));
  return 0;
}
