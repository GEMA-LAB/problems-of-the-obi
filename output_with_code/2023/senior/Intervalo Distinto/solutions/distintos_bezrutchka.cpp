// OBI 2023 - Fase 2
// Distintos - Solução O(N) gulosa usando dois ponteiros
// Mateus Bezrutchka
// 
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 200100;
int v[MAXN];
int ultimo_id[MAXN];
int n;
 
int solve() {
  int resp = 0;
  int inicio = 1;
  // para o fim atual, inicio guarda o menor índice
  // tal que [inicio, fim] nao tem repetições
  for (int fim = 1; fim <= n; fim++) {
    int x = v[fim];
    if (ultimo_id[x] >= inicio) {
      inicio = ultimo_id[x] + 1;
    }
    resp = max(resp, fim - inicio + 1);
    ultimo_id[x] = fim;
  }
  return resp;
}
 
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
  }
  printf("%d\n", solve());
  return 0;
}
