/*
    OBI 2025 - Fase 2
    Matriz
*/

#include <bits/stdc++.h>
using namespace std; 

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); 

    int n, m; cin >> n >> m;
    vector<int> resp(2); 
    vector<vector<int>> mat(n, vector<int>(m)); 
    for( int i = 0; i < n; i++ )
        for( int j = 0; j < m; j++ ){
            cin >> mat[i][j]; 
            resp[(i + j + mat[i][j])%2]++;
        }

    cout << min(resp[0], resp[1]) << endl; 
    int opt = (( resp[0] < resp[1] ) ? 0 : 1 );
    for( int i = 0; i < n; i++ ){
        for( int j = 0; j < m; j++ ){   
            if( (i + j + mat[i][j])%2 == opt ) mat[i][j]++;
            cout << mat[i][j] << ((j == m - 1) ? "" : " ");
        }

        cout << endl;
    }
}