#include<bits/stdc++.h>
#define all(x) begin(x), end(x)
#define ff first
#define ss second
#define O_O
using namespace std;
template <typename T>
using bstring = basic_string<T>;
template <typename T>
using matrix = vector<vector<T>>;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using dbl = double;
using dbll = long double;
using ci = complex<int>;
using cl = complex<ll>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
const ll INFL = 4e18+25;
const int INF = 1e9+42;
const double EPS = 1e-7;
const int MOD = (1<<23)*17*7 + 1; // 998244353
const int SEED = chrono::high_resolution_clock::now().time_since_epoch().count();
const int MAXN = 1e6+1;
mt19937 rng(SEED);

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;

    vector<ll> best_suf(n+1);

    vector<ll> a(n), b(n);

    for(ll& i : a)
        cin >> i;

    for(ll& i : b)
        cin >> i;

    for(int i = n-1; i >= 0; i--){
        best_suf[i] = best_suf[i+1]+max(a[i], 2*b[i]);
    }

    if(k == 0){
        cout << best_suf[0] << '\n';
        return 0;
    }

    ll resp = 0;
    ll pref = 0;

    priority_queue<ll> pq;

    for(int i = 0; i < n; i++){
        pref+=b[i];
        pq.push(a[i]-b[i]);
        if(pq.size() >= k){
            while(pq.size() > k && pq.top() > 0)
                pref+=pq.top(), pq.pop();
            resp = max(resp, best_suf[i+1]+pref);
        }
    }
    while(pq.size() && pq.top() > 0){
        pref+=pq.top();
        pq.pop();
    }
    resp = max(pref,resp);

    cout << resp << '\n';

    
    return 0;

}