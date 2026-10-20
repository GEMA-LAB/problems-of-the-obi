
/*
    OBI 2025 - Fase 2
    Distintos
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

ll sum( ll a, ll b ){
  return (a + b)*(b - a + 1)/2;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    int q; cin >> q; 
    while( q-- ){
        ll l, a, b; cin >> l >> a >> b;
    
        if( a > l || a == b ){ cout << 1 << endl; continue; }
        if( sum( a, b - 1 ) < l ){ cout << b - a + 1 << endl; continue; }
    
        ld maxi = (-1 + sqrt(4*a*a - 4*a + 8*l + 1))/2.0;
        int val = (int)ceil(maxi);
        cout << val - a + 1 << endl;
    }

}
