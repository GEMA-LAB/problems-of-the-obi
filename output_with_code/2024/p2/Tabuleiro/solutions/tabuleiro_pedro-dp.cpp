#include <bits/stdc++.h>

using namespace std;

const int M = 1'000'000'007;

signed main() {
    int n; cin >> n;
    vector<int> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; --i) {
        long long x = dp[i + 1];
        if (i + 2 <= n) x += 2 * dp[i + 2];
        if (i + 3 <= n) x += 2 * dp[i + 3];
        x %= M;
        dp[i] = x;
    }
    int ans = dp[0];
    cout << ans << '\n';

    return 0;
}
