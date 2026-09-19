#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  map<int, int> mp;
  for (int i = 0; i < n; i++) {
    int alt;
    cin >> alt;
    mp[alt]++;
  }

  int resp = 0;
  for (auto [alt, cnt]: mp) {
    resp += cnt / 2;
  }

  cout << resp << endl;
  return 0;
}
