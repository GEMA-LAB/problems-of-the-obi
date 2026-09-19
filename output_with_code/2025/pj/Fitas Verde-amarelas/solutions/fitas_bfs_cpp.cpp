#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
const int MAXC = MAXN * MAXN;
int dl[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int n, m;
char grid[MAXN][MAXN];
int comp[MAXN][MAXN];
int comp_atual;
int fitas_hor[MAXC], fitas_ver[MAXC];

// busca em largura
void bfs(int orig_l, int orig_c) {
  queue<pair<int,int>> q;
  q.push({orig_l, orig_c});
  comp[orig_l][orig_c] = comp_atual;

  while (!q.empty()) {
    pair<int, int> p = q.front();
    int l = p.first, c = p.second;
    q.pop();

    for (int i = 0; i < 4; i++) {
      int nl = l + dl[i];
      int nc = c + dc[i];
      if (nl <= 0 || nl > n || nc <= 0 || nc > m) continue;
      if (grid[nl][nc] == '#' && !comp[nl][nc]) {
        comp[nl][nc] = comp_atual;
        q.push({nl, nc});
      }
    }
  }
}

int main() {
  cin >> n >> m;
  for (int l = 1; l <= n; l++) {
    for (int c = 1; c <= m; c++) {
      cin >> grid[l][c];
    }
  }

  // encontra componentes conexas
  for (int l = 1; l <= n; l++) {
    for (int c = 1; c <= m; c++) {
      if (grid[l][c] == '#' && !comp[l][c]) {
        comp_atual++;
        bfs(l, c);
      }
    }
  }

  // testa colocar fitas horizontais em cada componente
  for (int l = 1; l <= n; l++) {
    for (int c = 1; c <= m; c++) {
      if (grid[l][c] != '#') continue;
      if (c == 1 || grid[l][c - 1] != '#') {
        fitas_hor[comp[l][c]]++;
      }
    }
  }

  // testa colocar fitas verticais em cada componente
  for (int c = 1; c <= m; c++) {
    for (int l = 1; l <= n; l++) {
      if (grid[l][c] != '#') continue;
      if (l == 1 || grid[l - 1][c] != '#') {
        fitas_ver[comp[l][c]]++;
      }
    }
  }

  // pega a melhor opcao pra cada componente
  int resp = 0;
  for (int i = 1; i <= comp_atual; i++) {
    resp += min(fitas_hor[i], fitas_ver[i]);
  }

  cout << resp << endl;
  return 0;
}
