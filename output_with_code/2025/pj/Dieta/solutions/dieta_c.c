/*
    OBI 2025 - Fase 1
    Dieta
*/

#include <stdio.h>

int main(){
    int n, m; 
    scanf("%d %d", &n, &m );

    int calorias = 0;
    for( int i = 0; i < n; i++ ){
        int p, g, c;
        scanf("%d %d %d", &p, &g, &c );
        calorias += 4*p + 9*g + 4*c; 
    }

    printf("%d\n", m - calorias);
}