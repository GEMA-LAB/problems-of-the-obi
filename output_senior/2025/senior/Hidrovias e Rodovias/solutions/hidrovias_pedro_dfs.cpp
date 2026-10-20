/*
    OBI 2025 - Fase 3
    Hidrovias
*/


#include <bits/stdc++.h>
using namespace std; 

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    int n, m, k; cin >> n >> m >> k; 
    
    vector<vector<pair<int, int>>> adj(n); 
    while( m-- ){
        int a, b, c; cin >> a >> b >> c; 
        a--; b--; c--; 
        adj[a].push_back({ b, c }); 
        adj[b].push_back({ a, c });
    }

    vector<int> marc(n, -1); 

    // dfs retorna 2*(arestas - vertices) na componente
    function<int(int, int)> dfs = [&]( int cur, int t ){
        if( marc[cur] == t ) return 0; 
        marc[cur] = t; 
        int soma = -2; 
        for( auto [viz, type] : adj[cur] ) if( type <= t ) soma += dfs( viz, t ) + 1;
        return soma; 
    };

    for( int i = 0; i < n; i++ ) if( marc[i] == -1 ){
        int x = dfs( i, 0 )/2; 
        if( x >= 0 ){ cout << "N" << endl; return 0; }
    }

    for( int i = 0; i < n; i++ ) if( marc[i] == 0 ){
        int x = dfs(i, 1)/2; 
        k -= (x + 1);
        if( k < 0 ){ cout << "N" << endl; return 0; }
    }

    cout << "S" << endl;

}