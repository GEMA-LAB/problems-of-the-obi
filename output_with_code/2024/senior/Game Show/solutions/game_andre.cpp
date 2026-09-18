#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
const int INF = 1000000000;
int dp[MAXN];
int main() {
  int n;
  scanf("%d", &n);
  char seq[n];
  scanf(" %s", seq);
  int num = 1;
  for(int i = 0; i < n; i++) {
    num *= 2;
    if(seq[i] == 'D') num++;
  }
  printf("%d\n", num);
}