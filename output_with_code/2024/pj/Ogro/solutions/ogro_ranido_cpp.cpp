// OBI2024 - Fase 1
// Ogro

#include <bits/stdc++.h>
using namespace std;

int main() {
  int e, d, res;

  cin >> e >> d;

  if (e > d) {
    res = e + d;
  }
  else {
    res = 2 * (d - e);
  }

  cout << res << endl;

}
