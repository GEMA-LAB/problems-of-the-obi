#include <bits/stdc++.h>
using namespace std;
#define int long long

const int inf = 1e18;

int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n+1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> pf(n+1,vector<int>(30,0));

    for(int i = 1; i <= n; i++) {
        for(int b = 0; b < 30; b++) {
            pf[i][b] = pf[i-1][b] + (((1<<b)&a[i])!=0);
        }
    }

    vector<int> dp(n+1);
    vector<map<int,int>> dps(n+1);
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        int j = i-(k-1);
        
        if(j >= 1) {
            int s = 0;
            
            for(int b = 0; b < 30; b++) {
                if(pf[i][b] - pf[j][b] != 0) s+= (1<<b);
            }

            for(auto x : dps[j]) {
                int news = (x.first|s);
                if(dps[i].count(news) == 0) dps[i][news] = x.second;
                else dps[i][news] = min(dps[i][news],x.second);
            }
        }

        if(dps[i].count(a[i]) == 0) dps[i][a[i]] = dp[i-1];
        else dps[i][a[i]] = min(dps[i][a[i]],dp[i-1]);

        dp[i] = inf;
        for(auto x : dps[i]) {
            dp[i] = min(dp[i],x.first+x.second);
        }

    }

    cout << dp[n] << endl;
}

// i-j+1 == 1
// i == j mod (k-1)