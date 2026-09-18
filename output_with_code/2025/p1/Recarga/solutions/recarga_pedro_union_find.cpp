/*
    OBI 2025 - Fase 3
    Recarga
*/

#include <bits/stdc++.h>
using namespace std; 

using ll = long long;
using pll = pair<ll, ll>;

const ll inf = 1e18;

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);  
    while( m-- ){
        int a, b, c; cin >> a >> b >> c; 
        a--; b--;
        adj[a].push_back({ b, c }); 
        adj[b].push_back({ a, c });
    }

    int k; cin >> k; 
    vector<int> sources(k); 
    for( int &x : sources ){ cin >> x; x--; }
    sources.push_back(n - 1);

    auto dijkstra = [&]( vector<int> &source ){
        set<pll> s; 
        vector<ll> dist(n, inf), origem(n, -1);  

        for( int source : sources ){
            dist[source] = 0; 
            origem[source] = source; 
            s.insert({ 0, source }); 
        }

        while( !s.empty() ){
            int cur = s.begin()->second; 
            s.erase(s.begin()); 
            
            for( auto [viz, d] : adj[cur] ) if( dist[viz] > dist[cur] + d ){
                s.erase({ dist[viz], viz }); 
                dist[viz] = dist[cur] + d; 
                s.insert({ dist[viz], viz });

                origem[viz] = origem[cur]; 
            }   
        }

        return make_pair( dist, origem ); 
    };

    auto [dist, origem] = dijkstra( sources ); 

    vector<int> pai(n); 
    iota( pai.begin(), pai.end(), 0 ); 

    function<int(int)> find = [&]( int a ){
        return (( a == pai[a] ) ? a : pai[a] = find(pai[a])); 
    };

    auto join = [&]( int a, int b ){
        pai[find(a)] = find(b); 
    };

    vector<tuple<ll, int, int>> v; 
    for( int i = 0; i < n; i++ )
        for( auto [j, d] : adj[i] ) 
            if( origem[i] != origem[j] && i < j ) 
                v.emplace_back( dist[i] + dist[j] + d, origem[i], origem[j] );

    sort( v.begin(), v.end() ); 

    for( auto [c, a, b] : v ){
        join( a, b ); 
        if( find(0) == find(n - 1) ){ cout << c << endl; return 0; }
    }
}