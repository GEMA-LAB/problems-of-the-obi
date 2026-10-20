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
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef double dbl;
typedef long double dbll; 
const ll INFL = 4e18+25;
const int INF = 1e9+42;
const double EPS = 1e-7;
const int MOD = (1<<23)*17*7 + 1; // 998244353
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
const int MAXN = 1e6+1;

/*
from https://github.com/defnotmee/definitely-not-a-lib

Usage: BIT(n) -> creates array arr of size n where you can
make point updates and prefix queries (0-indexed!) in O(log(n))

BIT::merge(a, b) -> merges b into element a. By default a+=b.
(must be commutative and associative)

BIT::update(id, x) -> merge(arr[i],x) for every i <= id

BIT::query(id) -> initializes ret = T(), does merge(ret, arr[i])
for every i <= id, returns ret.
*/

#ifndef O_O
#include"../utility/template.cpp"
#endif

template<typename T = ll>
struct BIT{
    vector<T> bit;

    BIT(int n = 0){
        bit = vector<T>(n+1);
    }
    
    inline void merge(T& a, T b){
        a+=b;
    }

    void update(int id, T x){
        id++;
        while(id < bit.size()){
            merge(bit[id],x);
            id+=id&-id;
        }
    }

    T query(int id){
        id++;
        T ret = T();
        while(id){
            merge(ret,bit[id]);
            id-=id&-id;
        }
        return ret;
    }
};

struct reta{
    ll a, b;

    ll eval(ll x){
        return a*x+b;
    }
};

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n, x1,x2;

    cin >> n >> x1 >> x2;

    vector<pll> ys(n);

    set<ll> vals;

    for(auto& i : ys){
        reta cur;
        cin >> cur.a >> cur.b;
        i = {cur.eval(x1), cur.eval(x2)};
        // cerr << i.ff << ' ' << i.ss << '\n';
        vals.insert(i.ff);
        vals.insert(i.ss);
    }

    map<ll, ll> tl;

    for(ll i : vals)
        tl[i] = tl.size();
    

    for(auto&[y1, y2] : ys){
        y1 = tl[y1];
        y2 = tl[y2];
    }

    sort(all(ys) , [&](pll a, pll b){
        if(a.ff == b.ff)
            return a.ss > b.ss;
        return a.ff < b.ff;
    });

    BIT bit(vals.size());

    ll resp = 0;
    for(int i = 0; i < n; i++){
        int y2 = ys[i].ss;
        resp+=i-bit.query(y2-1);
        bit.update(y2,1);
    }

    cout << resp << '\n';

    
    return 0;

}