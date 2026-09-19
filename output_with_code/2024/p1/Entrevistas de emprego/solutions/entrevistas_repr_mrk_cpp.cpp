/*
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - define o representante de cada grupo de amigos
      como o menor ID no grupo
    - usa vetor de marcação para ver se algum representante
      aparece mais de uma vez em uma entrevista
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3001;
char tabela[MAXN][MAXN];
int representante[MAXN];
int candidato[MAXN];
bool mrk[MAXN];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf(" %c", &tabela[i][j]);
    }
  }

  // representante de um candidato == o amigo dele de menor ID;
  // dois candidatos são amigos se e somente se possuem
  // o mesmo representante
  for (int i = 1; i <= n; i++) {
    representante[i] = i;
    for (int j = 1; j < i; j++) {
      if (tabela[i][j] == '1' && representante[i] == i) {
        representante[i] = j;
      }
    }
  }

  int e;
  scanf("%d", &e);
  while (e--) {
    int k;
    scanf("%d", &k);
    bool possui_amigos = false;
    for (int i = 1; i <= k; i++) {
      scanf("%d", &candidato[i]);
      if (mrk[representante[candidato[i]]]) {
        possui_amigos = true;
      }
      mrk[representante[candidato[i]]] = true;
    }
    for (int i = 1; i <= k; i++) {
      mrk[representante[candidato[i]]] = false;
    }
    if (possui_amigos) printf("S\n");
    else printf("N\n");
  }
  return 0;
}
