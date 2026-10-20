/*
    OBI 2025 - Fase 1
    Fila
*/

#include <stdio.h>

int main(){
    int n; 
    scanf("%d", &n ); 

    int v[n];
    for( int i = 0; i < n; i++ ) scanf("%d", &v[i] );

    int maior = -1; 
    int nao_visiveis = 0;

    for( int i = n - 1; i >= 0; i-- ){
        if( v[i] <= maior ) nao_visiveis++;
        else maior = v[i];
    }

    printf("%d\n", nao_visiveis );
}