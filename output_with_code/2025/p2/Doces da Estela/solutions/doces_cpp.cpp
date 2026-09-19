#include <bits/stdc++.h>

using namespace std;

long long N, preco_total = 0;

int main (void) {
    cin>>N;
    for(int d = 1; d <= N; d++){
        if(N % d == 0){
            long long c = N / d;
            long long caixa_simples = (10 + 3 * d);
            long long caixa_enfeitada = (2 + c) * caixa_simples;
            long long pedido = caixa_enfeitada * c;
            preco_total += pedido;
        }
    }
    cout<<preco_total<<endl;
    return 0;
}
