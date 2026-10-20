/*
    OBI 2025 - Fase 1
    Fila
*/


#include <bits/stdc++.h>
using namespace std; 

int main(){
    int n; cin >> n; 

    vector<int> v(n); 
    for( int &x : v ) cin >> x; 

    reverse( v.begin(), v.end() ); // olhar o vetor de tras para frente

    int maior = -1;
    int nao_visiveis = 0; 
    for( int x : v ){
        if( x <= maior ) nao_visiveis++; 
        maior = max( maior, x ); 
    }

    cout << nao_visiveis << endl;
}
