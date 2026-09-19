/*
    OBI 2025 - Fase 2
    Placar
*/

#include <bits/stdc++.h>
using namespace std;

const int maxt = 101;

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); 

    vector<int> marc(maxt, -1);
    for( int i = 0; i < 2; i++ ){
        int k; cin >> k; 
        while( k-- ){
            int x; cin >> x; marc[x] = i; 
        }
    }

    vector<int> resp(2); 
    cout << 0 << " " << 0 << endl;
    for( int x : marc ) if( x != -1 ){
        resp[x]++; 
        cout << resp[0] << " " << resp[1] << endl;
    }
}