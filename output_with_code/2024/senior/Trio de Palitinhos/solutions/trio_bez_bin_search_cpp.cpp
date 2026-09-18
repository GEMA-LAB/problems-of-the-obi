#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000;
int v[MAXN];

int main() {
  int n;
  long long resp = 0LL;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> v[i];
  sort(v, v + n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int soma = v[i] + v[j];
      int ultimo_bom = lower_bound(v, v + n, soma) - v - 1;
      if (ultimo_bom > j) resp += ultimo_bom - j;
    }
  }
  cout << resp << endl;
  return 0;
}
