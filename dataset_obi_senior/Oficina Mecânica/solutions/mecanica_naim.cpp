#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
typedef long long ll;

const int N = 100100;
int t[N], f[N];

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,m ;
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> t[i];
    }
    for(int i=0;i<m;i++){
        cin >> f[i];
    }
    ll res=0;
    sort(t+1,t+1+n,greater<int>());
    sort(f,f+m);

    set<pair<ll,int>> S;
    for(int i=0;i<m;i++){
        S.insert({0, i});
    }
    for(int i=1;i<=n;i++){
        int id = S.begin()->second;
        ll tot = S.begin()->first;
        S.erase(S.begin());
        res += tot * t[i];
        S.insert( {tot + f[id], id} );
    }
    cout << res << endl;
}