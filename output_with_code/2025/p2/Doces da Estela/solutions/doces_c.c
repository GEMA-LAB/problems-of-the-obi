#include <stdio.h>

long long N, preco_total = 0;

int main (void) {
    scanf("%lld", &N);
    for(int d = 1; d <= N; d++){
        if(N % d == 0){
            long long c = N / d;
            long long caixa_simples = (10 + 3 * d);
            long long caixa_enfeitada = (2 + c) * caixa_simples;
            long long pedido = caixa_enfeitada * c;
            preco_total += pedido;
        }
    }
    printf("%lld\n", preco_total);
    return 0;
}
