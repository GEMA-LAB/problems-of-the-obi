#include <iostream>
using namespace std;
const int M = 1e9 + 7, MAXN = 1e5 + 5;

long long dp[MAXN];

long long f(int n){
    if(n < 0) return 0;
    if(dp[n] >= 0) return dp[n];
    return dp[n] = (f(n - 1) + 2 * f(n - 2) + 2 * f(n - 3)) % M;
}

int main() {
    int n; cin >> n;

    dp[0] = 1;
    for(int i = 1; i < MAXN; i++) dp[i] = -1;

    cout << f(n) << '\n';

    return 0;
}