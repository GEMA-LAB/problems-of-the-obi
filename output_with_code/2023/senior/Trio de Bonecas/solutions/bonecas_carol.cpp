#include <iostream>
#include <algorithm>

const int MAXK = 3010;
const int MAXN = 1e4+10;
const long long INF = 1e18+10;

using namespace std;

int n, k;
int t[MAXN];
long long dp[MAXN][MAXK];

int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> t[i];
    }
    sort(t+1, t+1+n);
    for(int i = 1; i <= k; i++){
        dp[0][i] = INF;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= k; j++){
            long long ans = dp[i-1][j];
            int used = (k-j)*3;
            if((n-i) > used && i > 1 && j){
                long long cost = t[i]-t[i-1];
                cost *= cost;
                ans = min(ans, dp[i-2][j-1]+cost);
            }
            dp[i][j] = ans;
        }
    }
    cout << dp[n][k] << "\n";
}