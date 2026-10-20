/*
    OBI 2025 - Fase 1
    Festa
*/

#include <bits/stdc++.h>
using namespace std; 

int main(){
    int e, s, m; cin >> e >> s >> m; 
    cout << 2*(max({ e, s, m }) - min({e, s, m})) << endl;
}