#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int v[MAXN], f[MAXN], prox[MAXN];
int main() {
  int n; scanf("%d", &n);
  for(int i = 0; i < n; i++) { 
    scanf("%d", &v[i]);
    prox[v[i]] = n;
  }
  f[n - 1] = n - 1;
  prox[v[n - 1]] = n - 1;
  int resp = 1;
  for(int i = n - 2; i >= 0; i--) {
    f[i] = min(f[i + 1], prox[v[i]] - 1);
    prox[v[i]] = i;
    resp = max(resp, f[i] - i + 1);
  }
  printf("%d\n", resp);
}