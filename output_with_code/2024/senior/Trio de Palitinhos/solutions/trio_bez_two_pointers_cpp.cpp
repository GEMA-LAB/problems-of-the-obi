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
    int l = 0;
    for (int r = i - 1; r >= 1; r--) {
      while (l < r && v[l] + v[r] <= v[i]) l++;
      if (l < r) {
        resp += (r - l);
      }
    }
  }
  cout << resp << endl;
  return 0;
}
