#include <bits/stdc++.h>
using namespace std;

vector <vector<int>> original;
vector <int> linha;
vector <int> coluna;

int main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(false);

  int l, c, t;
  cin >> l >> c >> t;

  original.resize(l + 1);
  for (int i = 1; i <= l; i++) {
    original[i].resize(c + 1);
    for (int j = 1; j <= c; j++) {
      original[i][j] = c * (i - 1) + j;
    }
  }
  linha.resize(l + 1);
  for (int i = 1; i <= l; i++) {
    linha[i] = i;
  }
  coluna.resize(c + 1);
  for (int j = 1; j <= c; j++) {
    coluna[j] = j;
  }


  while (t--) {
    char op;
    int a, b;
    cin >> op >> a >> b;
    if (op == 'L') {
      swap(linha[a], linha[b]);
    } else {
      swap(coluna[a], coluna[b]);
    }
  }

  vector <vector<int>> resposta;
  resposta.resize(l + 1);
  for (int i = 1; i <= l; i++) {
    resposta[i].resize(c + 1);
    for (int j = 1; j <= c; j++) {
      resposta[i][j] = original[linha[i]][coluna[j]];
    }
  }

  for (int i = 1; i <= l; i++) {
    for (int j = 1; j <= c; j++) {
      cout << resposta[i][j];
      if (j == c) cout << "\n";
      else cout << " ";
    }
  }

  return 0;
}
