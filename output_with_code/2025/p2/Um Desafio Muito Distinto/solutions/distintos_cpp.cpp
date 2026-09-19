/*
    OBI 2025 - Fase 2
    Distintos
*/


#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll sum( ll a, ll b ){
  return (a + b)*(b - a + 1)/2;
}

int bb( ll a, ll b, ll L ){
  ll l = a, r = b;
  while( l < r ){
    ll mid = (l + r)/2;
    if( sum( a, mid ) >= L ) r = mid;
    else l = mid + 1; 
  }

  return r - a + 1; 
}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 
    int q; cin >> q; 
    while( q-- ){
        ll l, a, b; cin >> l >> a >> b;
        cout << bb( a, b, l ) << '\n';
    }
}

