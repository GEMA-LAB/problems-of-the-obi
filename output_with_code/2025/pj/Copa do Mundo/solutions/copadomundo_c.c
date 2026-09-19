#include<stdio.h>

int main(){
    int N;
    int trash = scanf("%d", &N);

    if(N == 1958 || N == 1962 || N == 1970 || N == 1994 || N == 2002) printf("S\n");
    else printf("N\n");

    return 0;
}
