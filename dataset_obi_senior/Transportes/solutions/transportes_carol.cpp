#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
const int MAX = 1e5+10;
const int INF = 1e9+10;

using namespace std;

int n, m, k, a, b;
int p[MAX], d[MAX*5], u[MAX], v[MAX], t[MAX];
int chefe[MAX];
vector<pair<int,int> > adj[MAX*5];
map< pair<int,int> , int> mp;

int main() {
    cin >> n >> m >> k;
    for(int i = 1; i <= k; i++){
        cin >> p[i];
    }
    for(int i = 1; i <= m; i++){
        cin >> v[i] >> u[i] >> t[i];
    }
    cin >> a >> b;

    // compressao de cordenadas
    int curKey = 0;
    for(int i = 1; i <= m; i++){
        mp[ make_pair(v[i], t[i]) ] = 0;
        mp[ make_pair(u[i], t[i]) ] = 0;
    }
    for(auto &e: mp){
        e.second = ++curKey;
    }
    for(int i = 1; i <= n; i++){
        mp[ make_pair(i, k+1) ] = chefe[i] = ++curKey;
    }

    // novo grafo
    for(int i = 1; i <= m; i++){
        int v1 = mp[make_pair(v[i], t[i])];
        int v2 = mp[make_pair(u[i], t[i])];
        
        for(int j = 0; j < 2; j++){
            int chefao = chefe[v[i]];
            
            adj[v1].push_back(make_pair(v2, 0));
            adj[v1].push_back(make_pair(chefao, 0));
            adj[chefao].push_back(make_pair(v1, p[t[i]]));

            swap(v1, v2);
            swap(v[i], u[i]);
        }
    }

    // dijkstra
    for(int i = 1; i <= curKey; i++){
        d[i] = INF;
    }
    int sa = chefe[a];
    d[sa] = 0;

    priority_queue<pair<int,int> > q;
    q.push(make_pair(0,sa));

    while(!q.empty()){
        int dist = -q.top().first;
        int v = q.top().second;

        q.pop();

        if(d[v] != dist){
            continue;
        }

        for(auto e: adj[v]){
            int price = e.second;
            int viz = e.first;

            int dd = dist+price;

            if(dd < d[viz]){
                q.push(make_pair(-dd, viz));
                d[viz] = dd;
            }

        }

    }

    int sb = chefe[b];

    if(d[sb] == INF){
        d[sb] = -1;
    }

    cout << d[sb] << "\n";

}