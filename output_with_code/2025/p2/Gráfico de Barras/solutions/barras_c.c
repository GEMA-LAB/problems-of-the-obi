/*
    OBI 2025 - Fase 1
    Grafico de Barras
*/

#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n ); 

    int v[n]; 
    int maior = 0;
    for( int i = 0; i < n; i++ ){
        scanf("%d", &v[i] ); 
        if( v[i] > maior ) maior = v[i];
    }

    int matriz[maior][n]; 
    for( int i = 0; i < n; i++ )
        for( int j = 0; j < maior; j++ )
            matriz[j][i] = (( j >= maior - v[i]) ? 1 : 0 );
        
    for( int i = 0; i < maior; i++ ){
        for( int j = 0; j < n; j++ ) printf("%d ", matriz[i][j] ); 
        printf("\n");
    }
}