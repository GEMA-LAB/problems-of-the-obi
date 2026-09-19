#include<bits/stdc++.h>
using namespace std;
using lint = int64_t;

int main(){
    int n, q;
    cin>>n>>q;
    vector<array<int, 4>>query(q);
    vector<int>last(n);
    for(int i=0;i<q;i++){
        int op;
        cin>>op;
        if(op == 1){
            int a, b, w;
            cin>>a>>b>>w;
            a--, b--;
            last[a] = last[b] = i;
            query[i] = {1, a, b, w};
        }  
        else{
            int v;
            cin>>v;
            v--;
            query[i] = {2, v, -1, -1};
        }
    }
    vector<lint>ans(n), sum(n), sz(n);
    vector<int>p(n);
    for(int i=0;i<n;i++) p[i] = i, sz[i] = 1;

    auto find = [&](auto& self, int u)->int {
        if(p[u] == u) return u;
        return p[u] = self(self, p[u]);
    };
    
    auto join = [&](int u, int v, lint w)->void {
        u = find(find, u);
        v = find(find, v);
        ans[u] = ans[u] + ans[v] + sum[u] * sz[v] + sum[v] * sz[u] + w * sz[u] * sz[v];
        sum[u] = sum[u] + sum[v] + w * sz[v];
        sz[u] = sz[u] + sz[v];
        p[v] = u;
    };

    for(auto [op, a, b, w] : query){
        if(op == 1){
            if(last[a] < last[b]) swap(a, b);
            join(a, b, w);
        }
        else if(op == 2){
            int v = find(find, a);
            cout<<ans[v]<<"\n";
        }
    }    

    return 0;
}