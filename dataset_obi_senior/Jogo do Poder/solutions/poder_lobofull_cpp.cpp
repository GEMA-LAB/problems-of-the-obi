#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18 + 10;
const int inf1 = 1e9 + 10;
#define int long long
#define dbl long double
#define endl '\n'
#define sc second
#define fr first
#define mp make_pair
#define pb push_back
#define all(x) x.begin(), x.end()
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
const int maxn = -1;

int n, m;
vector<vector<int>> a, ans, dsz, dsa;
vector<vector<pair<int,int>>> ds;
vector<vector<vector<pair<int,int>>>> dsans;
vector<vector<set<pair<int,pair<int,int>>>>> g;

vector<pair<int,int>> adj = {{0,1},{0,-1},{1,0},{-1,0}};

pair<int,int> find(int i, int j) {
    if(mp(i,j) == ds[i][j]) return mp(i,j);
    return ds[i][j] = find(ds[i][j].fr,ds[i][j].sc);
}

void join(int i1, int j1, int i2, int j2) {
    if(dsz[i1][j1] < dsz[i2][j2]) {
        swap(i1,i2);
        swap(j1,j2);
    }

    dsz[i1][j1]+= dsz[i2][j2];
    ds[i2][j2] = mp(i1,j1);
    dsa[i1][j1]+= dsa[i2][j2];

    if(g[i1][j1].size() < g[i2][j2].size()) swap(g[i1][j1],g[i2][j2]);
    for(auto X : g[i2][j2]) {
        g[i1][j1].insert(X);
    }
    if(dsans[i1][j1].size() < dsans[i2][j2].size()) swap(dsans[i1][j1],dsans[i2][j2]);
    for(auto X : dsans[i2][j2]) {
        dsans[i1][j1].pb(X);
    }
}

void solve() {
    cin >> n >> m;

    a.resize(n+5,vector<int>(m+5));
    ans.resize(n+5,vector<int>(m+5));
    dsz.resize(n+5,vector<int>(m+5));
    dsa.resize(n+5,vector<int>(m+5));
    ds.resize(n+5,vector<pair<int,int>>(m+5));
    dsans.resize(n+5,vector<vector<pair<int,int>>>(m+5));
    g.resize(n+5,vector<set<pair<int,pair<int,int>>>>(m+5));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            ds[i][j] = mp(i,j);
            dsz[i][j] = 1;
            dsa[i][j] = a[i][j];
            dsans[i][j].pb(mp(i,j));
            for(auto X : adj) {
                int i1 = i+X.fr;
                int j1 = j+X.sc;
                if(i1 >= 1 and j1 >= 1 and i1 <= n and j1 <= m) {
                    g[i][j].insert(mp(a[i1][j1],mp(i1,j1)));
                }
            }

            pq.push(mp(a[i][j],mp(i,j)));
        }
    }
    while(pq.size()) {
        int i = pq.top().sc.fr;
        int j = pq.top().sc.sc;
        int valpq = pq.top().fr;
        pq.pop();
        if(valpq != dsa[i][j] or mp(i,j) != find(i,j)) {
            continue;
        }

        pair<int,int> f;
        f = find(i,j); i=f.fr; j=f.sc;
        if(g[i][j].size() == 0 or g[i][j].begin()->fr > dsa[i][j]) {
            for(auto X : dsans[i][j]) {
                int i1 = X.fr;
                int j1 = X.sc;
                ans[i1][j1] = dsa[i][j];
            }
            dsans[i][j].clear();
        }
        else {
            int i1 = g[i][j].begin()->sc.fr;
            int j1 = g[i][j].begin()->sc.sc;
            g[i][j].erase(g[i][j].begin());
            f = find(i1,j1); i1=f.fr; j1=f.sc;
            if(mp(i,j) != mp(i1,j1)) {
                join(i,j,i1,j1);
            }
            f = find(i,j); i=f.fr; j=f.sc;

            pq.push(mp(dsa[i][j],mp(i,j)));
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0);

    // #ifndef ONLINE_JUDGE
    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);
    // #endif

    int tt = 1;
    // cin >> tt;
    while(tt--) {
        solve();
    }

}
