#include <bits/stdc++.h>
using namespace std;

int main() {
  int d;
  cin >> d;

  int resp = 2000;
  for (int ponto = 0; ponto <= 2000; ponto += 400) {
    int dist_ponto;
    if (d > ponto) dist_ponto = d - ponto;
    else dist_ponto = ponto - d;
    resp = min(resp, dist_ponto);
  }

  cout << resp << endl;
  return 0;
}
