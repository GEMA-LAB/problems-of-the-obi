/*
  OBI 2025 - Fase 1
  Fila
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int resp = 0;
  int mais_alto = a[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    if (mais_alto >= a[i]) {
      resp++;
    } else {
      mais_alto = a[i];
    }
  }

  cout << resp << endl;
  return 0;
}
