/**
 * OBI 2023 - Fase 3
 * Tesouro da Quadradônia - Solução O(N^2) usando matriz auxiliar
 *                          para marcar posições visitadas
 * Mateus Bezrutchka
 **/
#include <iostream>
using namespace std;

const int MAXN = 1001;
char mapa[MAXN][MAXN];
// marca areas que eu ja visitei antes para identificar loop infinito
bool visitado[MAXN][MAXN];

int main() {
  int n, a, b;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> mapa[i][j];
    }
  }
  cin >> a >> b;

  // (x, y) mantém a posição atual
  int x = a;
  int y = b;
  int minutos = 0;

  while (1) {
    if (x < 1 || x > n || y < 1 || y > n) {
      // caiu na água
      cout << -1 << endl;
      return 0;
    }
    if (visitado[x][y]) {
      // entrou em loop
      cout << 0 << endl;
      return 0;
    }
    if (mapa[x][y] == 'X') {
      // encontrou o tesouro
      cout << minutos << endl;
      return 0;
    }
    // move pra próxima área
    visitado[x][y] = true;
    minutos++;
    if (mapa[x][y] == 'N') x--;
    else if (mapa[x][y] == 'S') x++;
    else if (mapa[x][y] == 'O') y--;
    else y++;
  }

  return 0;
}
