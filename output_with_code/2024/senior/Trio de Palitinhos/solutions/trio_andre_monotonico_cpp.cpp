#include <bits/stdc++.h>
using namespace std;
const int MAXN=3010;
int a[MAXN];
int main() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) scanf("%d", &a[i]);
  sort(a, a + n);
  long long int resp = 0;
  for(int i = 0; i <= n - 3; i++) {
    int k = i + 2;
    for(int j = i + 1; j <= n - 2; j++) {
      k = max(k, j + 1);
      while(k < n && (a[i] + a[j] > a[k])) k++;
      resp += (k - 1) - j;
    }
  }
  printf("%lld\n", resp);
}
