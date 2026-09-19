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

int n, k, v[100005], freq[100005];
ll ans;

int main(){_
    cin>>n>>k;

    for(int i=0;i<n;i++) cin>>v[i];

    int l = 0, r = 0, diff = 0;

    while(l<n){
        while(diff<k && r<n){
            if(!freq[v[r]]) diff++;
            freq[v[r++]]++;
        }
        if(diff>=k) ans += (n-r+1);

        if(freq[v[l]] == 1) diff--;
        freq[v[l++]]--;
    }

    cout<<ans<<'\n';
  
    return 0;
}