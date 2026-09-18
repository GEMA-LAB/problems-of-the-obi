#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
const int INF = 1000000000;
int dp[MAXN];
int main() {
  int n;
  scanf("%d", &n);
  dp[0] = 0;
  for(int i = 1; i <= n; i++) {
    dp[i] = INF;
    int num = i;
    while(num > 0) {
      int digito = num%10;
      dp[i] = min(dp[i], dp[i - digito] + 1);
      num = num/10;
    }
  }
  printf("%d\n", dp[n]);
}