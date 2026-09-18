#include <bits/stdc++.h>
using namespace std;
#define int long long



int32_t main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> g(n+1);
    vector<array<int,3>> edgs;
    for(int i = 1; i <= m; i++) {
        int u,v,w;
        cin >> u >> v >> w;

        g[u].push_back({v,w});
        g[v].push_back({u,w});
        edgs.push_back({u,v,w});
    }

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    vector<int> d(n+1,(int)1e14), s(n+1);
    int k;
    cin >> k;
    while(k--) {
        int x; cin >> x;
        d[x] = 0;
        s[x] = x;
        pq.push({d[x],x});
    }
    d[n] = 0;
    s[n] = n;
    pq.push({d[n],n});

    while(pq.size()) {
        int u = pq.top().second;
        int dis = pq.top().first;
        pq.pop();

        if(dis != d[u]) continue;

        for(auto V : g[u]) {
            int v = V.first;
            int w = V.second;

            if(d[v] > d[u]+w) {
                d[v] = d[u]+w;
                s[v] = s[u];
                pq.push({d[v],v});
            }
        }
    }


    int l = 0;
    int r = 1e14;
    int ans = -1;
    while(l <= r) {
        int mid = (l+r)>>1;

        vector<vector<int>> gg(n+1);
        for(auto x : edgs) {
            int u = x[0];
            int v = x[1];
            int w = x[2];

            if(d[u]+w+d[v] <= mid) {
                gg[s[u]].push_back(s[v]);
                gg[s[v]].push_back(s[u]);
            }
        }

        vector<int> mark(n+1,0);
        queue<int> q;
        q.push(1);
        mark[1] = 1;
        while(q.size()) {
            int u = q.front();
            q.pop();

            for(auto v : gg[u]) {
                if(!mark[v]) {
                    mark[v] = 1;
                    q.push(v);
                }
            }
        }

        if(mark[n] == 1) {
            ans = mid;
            r = mid-1;
        }
        else {
            l = mid+1;
        }
    }

    cout << ans << endl;

}
// full