#include <stdio.h>

int max( int a, int b ){
    return (( a > b ) ? a : b ); 
}

int min( int a, int b ){
    return (( a > b ) ? b : a ); 
}

int main(){
    int e, s, m; scanf("%d %d %d", &e, &s, &m );
    int maior = max( e, max( s, m ) ); 
    int menor = min( e, min( s, m ) ); 
    printf("%d\n", 2*(maior - menor)); 
}