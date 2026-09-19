/* Letras - Felipe Abella */

#include <algorithm>
#include <cstdio>
#include <cstring>

#define MAXN 300000

using namespace std;

char seq[MAXN+1];
int dp[MAXN+1][26];

int main() {
  scanf(" %s", seq);
  int n = strlen(seq);

  for (int c = 0; c < 26; c++) dp[n][c] = 0;
  for (int i = n-1; i >= 0; i--)
    for (int c = 0; c < 26; c++) {
      dp[i][c] = dp[i+1][c];
      if (seq[i] - 'A' >= c)
	dp[i][c] = max(dp[i][c], 1 + dp[i+1][seq[i] - 'A']);
    }

  printf("%d\n", dp[0][0]);
  return 0;
}
