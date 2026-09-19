/*
    OBI 2025 - Fase 1
    Dieta
*/

#include <iostream>
using namespace std; 

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m; 
    cin >> n >> m; 

    int calorias = 0;
    for( int i = 0; i < n; i++ ){
        int p, g, c;
        cin >> p >> g >> c; 
        calorias += 4*p + 9*g + 4*c; 
    }

    cout << m - calorias << endl;
}
