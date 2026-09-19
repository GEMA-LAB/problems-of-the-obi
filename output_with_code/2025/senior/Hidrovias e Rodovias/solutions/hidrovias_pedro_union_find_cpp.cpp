/*
    OBI 2025 - Fase 3
    Hidrovias
*/


#include <bits/stdc++.h>
using namespace std; 

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    int n, m, k; cin >> n >> m >> k; 

    vector<tuple<int, int, int>> arestas; 
    while( m-- ){
        int a, b, c; cin >> a >> b >> c;
        a--; b--; c--;  
        arestas.emplace_back( c, a, b );
    }

    sort( arestas.begin(), arestas.end() );

    vector<int> pai(n); 
    iota( pai.begin(), pai.end(), 0 ); 

    function<int(int)> find = [&]( int a ){
        return (( a == pai[a] ) ? a : pai[a] = find(pai[a])); 
    };

    auto join = [&]( int a, int b ){
        pai[find(a)] = find(b); 
    };

    for( auto [c, a, b] : arestas ){
        if( find(a) != find(b) ) join( a, b ); 
        else{
            if( c == 0 ){ cout << "N" << endl; return 0; }
            if( --k < 0 ){ cout << "N" << endl; return 0; }
        } 
    }
    cout << "S" << endl;
}