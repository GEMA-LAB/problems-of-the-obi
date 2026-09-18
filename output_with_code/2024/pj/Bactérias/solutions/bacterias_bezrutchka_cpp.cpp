#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, p;
  cin >> n >> p;

  int pot = 1, r = 0;
  while (true) {
    if (pot * p > n) break;
    pot *= p;
    r++;
  }

  cout << r << endl;
  return 0;
}
