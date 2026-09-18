#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, p;
  cin >> n >> p;
  int lg = (int) (log(n) / log(p));
  cout << lg << endl;
  return 0;
}
