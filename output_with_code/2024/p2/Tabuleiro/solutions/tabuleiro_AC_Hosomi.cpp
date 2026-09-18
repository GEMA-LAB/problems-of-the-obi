#include <bits/stdc++.h>
using namespace std;
#define _ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define f first
#define s second
#define L(x) (x<<1)
#define R(x) ((x<<1)+1)
#define lsb(x) ((x)&(-x))
#define inf (int)1e9
#define linf (ll)1e17
typedef pair<int,int> ii;
typedef vector<int> vi;
const ll mod = 1e9 + 7;

int n;
ll dp[100005];

int main(){_
    cin>>n; dp[0] = 1; dp[1] = 1; dp[2] = 3; dp[3] = 7;

    for(int i=4;i<=n;i++) dp[i] = (dp[i-1] + 2*dp[i-2] + 2*dp[i-3])%mod;

    cout<<dp[n]<<'\n';

    return 0;
}