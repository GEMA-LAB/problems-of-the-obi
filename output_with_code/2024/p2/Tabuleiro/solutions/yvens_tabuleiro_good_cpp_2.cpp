#include <iostream>
using namespace std;
const int M = 1e9 + 7, MAXN = 1e5 + 5;

long long dp[MAXN];

int main() {
    int n; cin >> n;

    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 3;

    for(int i = 3; i <= n; i++)
        dp[i] = (dp[i - 1] + 2 * dp[i - 2] + 2 * dp[i - 3]) % M;

    cout << dp[n] << '\n';

    return 0;
}