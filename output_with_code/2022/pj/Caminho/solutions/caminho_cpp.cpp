// OBI2022
// Tarefa Caminho
// André Sousa

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500010;
int p[2 * MAXN];

int main() {
  int n; scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
  for(int i = n + 1; i <= 2 * n; i++) p[i] = p[i - n];
  
  int resp = 0;
  int cur = 0;
  for(int i = 2; i <= 2 * n; i++) {
    if(p[i] + p[i - 1] < 1000) cur++;
    else cur = 0;
    
    resp = max(resp, cur);
  }
  
  resp = min(resp, n);
  printf("%d\n", resp);
}
