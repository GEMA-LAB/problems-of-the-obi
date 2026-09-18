#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110;
int mat[MAXN][MAXN];
int main() {
  int a, n, m; scanf("%d %d %d", &a, &n, &m);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
      scanf("%d", &mat[i][j]);
  
  int resp = -1;
  for(int i = n - 1; i >= 0; i--) {
    int qtd = 0, cur = 0;
    for(int j = 0; j < m; j++) {
      if(mat[i][j] == 0) {
        cur++;
        qtd = max(qtd, cur);
      } else cur = 0;
    }
    if(qtd >= a) {
      resp = n - i;
      break;
    }
  }
  
  printf("%d\n", resp);
}

