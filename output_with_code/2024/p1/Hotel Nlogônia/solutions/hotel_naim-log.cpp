#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 200100;
const ll inf = 1e18;
ll v[N];
ll pre[N];
ll sum(int l,int r){
    return pre[r] - pre[l-1];
}

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,d;
    ll w;
    cin >> n >> d >> w;
    for(int i=1;i<=n;i++){
        cin >> v[i];
        pre[i] = pre[i-1] + v[i];
    }
    v[n+1] = inf;
    pre[n+1] = 2*inf;
    int ans = min(d, n);
    multiset<ll> S;
    S.insert(sum(1,d));
    for(int i=1,j=d;i + d - 1 <= n;i++){
        while(sum(i,j) - *S.rbegin() <= w){
            j++;
            if(j <= n)S.insert(sum(j-d+1,j));
        }
        ans = max(ans,j-i); // maior valido eh [i,j)
        // andar i. Preciso tirar range [i,i+d)
        S.erase(S.find(sum(i,i + d - 1)));
    }
    cout << ans << endl;
    return 0;
}

/*
Ex:
5 3 5
4 10 10 10 1
Resp: 5

7 3 4
4 10 10 10 1 1 1
resp: 6
*/
