/*
    OBI 2025 Fase 3
    Empregos
*/

#include <bits/stdc++.h>
using namespace std; 

using ll = long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    int n, k; cin >> n >> k; 

    vector<int> a(n), b(n);
    
    for( int i = 0; i < n; i++ ) cin >> a[i]; 
    for( int i = 0; i < n; i++ ) cin >> b[i]; 
    
    ll best_prefix = 0, answer = 0; 
    vector<ll> best_suffix(n + 1); 
    for( int i = n - 1; i >= 0; i-- ){
        best_suffix[i] = best_suffix[i + 1] + max( a[i], 2*b[i] ); 
        answer += max( a[i], b[i] ); 
    }
    
    if( k == 0 ){ cout << best_suffix[0] << endl; return 0; }

    multiset<int> k_smallest; 


    for( int i = 0; i < n; i++ ){
        best_prefix += b[i]; 
        k_smallest.insert(a[i] - b[i]); 
        if( i + 1 < k ) continue; 

        if( k_smallest.size() > k && *k_smallest.rbegin() >= 0 ){
            best_prefix += *k_smallest.rbegin();
            k_smallest.erase(prev(k_smallest.end()));
        }

        answer = max( answer, best_prefix + best_suffix[i + 1] );
    }

    cout << answer << endl;
}