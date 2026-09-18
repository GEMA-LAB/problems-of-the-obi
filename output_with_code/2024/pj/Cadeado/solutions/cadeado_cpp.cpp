/*
OBI 2024 - Fase 3
  Cadeado
  Solução em O(N) com iteração e análise de casos
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  int clicks = 0;
  for (int i = 0; i < n; i++) {
    int c, s;
    cin >> c >> s;
    if (c > s) {
      int hor = c - s;
      int antihor = 10 + s - c;
      clicks += min(hor, antihor);
    } else {
      int hor = s - c;
      int antihor = 10 + c - s;
      clicks += min(hor, antihor);
    }
  }
  cout << clicks << endl;
  return 0;
}
