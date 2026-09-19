/*
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - modela os grupos de amigos como componentes conexas
      de um grafo. Faz DFS para identificar os grupos de amigos
    - usa vetor de marcação para ver se alguma componente
      aparece mais de uma vez em uma entrevista
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3001;
char tabela[MAXN][MAXN];
int componente[MAXN];
bool mrk[MAXN];
int candidato[MAXN];
int n;

void dfs(int v, int c) {
  componente[v] = c;
  for (int w = 1; w <= n; w++) {
    if (componente[w] > 0 || tabela[v][w] == '0') continue;
    dfs(w, c);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf(" %c", &tabela[i][j]);
    }
  }

  int comp_atual = 1;
  for (int i = 1; i <= n; i++) {
    if (!componente[i]) {
      dfs(i, comp_atual);
      comp_atual++;
    }
  }

  int e;
  scanf("%d", &e);
  while (e--) {
    int k;
    bool possui_amigos = false;
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
      scanf("%d", &candidato[i]);
      if (mrk[componente[candidato[i]]]) {
        possui_amigos = true;
      }
      mrk[componente[candidato[i]]] = true;
    }
    for (int i = 1; i <= k; i++) {
      mrk[componente[candidato[i]]] = false;
    }
    if (possui_amigos) printf("S\n");
    else printf("N\n");
  }
  return 0;
}
