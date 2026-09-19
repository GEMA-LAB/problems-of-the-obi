#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
int preco[MAXN], tipo[MAXN], cliente[MAXN];

int main() {
  int n, c;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> tipo[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> preco[i];
  }
  cin >> c;
  for (int i = 0; i < c; i++) {
    cin >> cliente[i];
  }

  vector<int> precos[3];
  for (int i = 0; i < n; i++) {
    if (tipo[i] == 1) precos[1].push_back(preco[i]);
    else precos[2].push_back(preco[i]);
  }
  sort(precos[1].rbegin(), precos[1].rend());
  sort(precos[2].rbegin(), precos[2].rend());

  int resp = 0;
  for (int i = 0; i < c; i++) {
    int tipo = -1;
    if (cliente[i] == 1) {
      if (!precos[1].empty()) tipo = 1;
    } else if (cliente[i] == 2) {
      if (!precos[2].empty()) tipo = 2;
    } else {
      // indeciso
      if (precos[1].empty() && precos[2].empty()) tipo = -1;
      else if (precos[1].empty()) tipo = 2;
      else if (precos[2].empty()) tipo = 1;
      else if (precos[1].back() <= precos[2].back()) tipo = 1;
      else tipo = 2;
    }
    if (tipo == -1 || precos[tipo].empty()) continue;
    resp += precos[tipo].back();
    precos[tipo].pop_back();
  }
  cout << resp << endl;
  return 0;
}
