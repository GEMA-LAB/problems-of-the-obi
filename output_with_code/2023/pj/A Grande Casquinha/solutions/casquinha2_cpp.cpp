#include"bits/stdc++.h"

using namespace std;

int X[2000000];
int prox_ind[2000000];
int prox_val[10000001];
int tabela[20][2000000];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int N, S;
    cin>>N>>S;
    for(int i = 0; i < N; i++)
        cin>>X[i];
    for(int i = N-1; i >= 0; i--){
        prox_ind[i] = N;
        if(prox_val[X[i]] != 0)
            prox_ind[i] = prox_val[X[i]];
        prox_val[X[i]] = i;
    }

    for(int i = 0; i < N; i++)
        tabela[0][i] = prox_ind[i];
    for(int i = 1; i <= __lg(N); i++)
        for(int j = 0; j + (1<<i) <= N; j++)
            tabela[i][j] = min(tabela[i-1][j], tabela[i-1][j + (1<<(i-1))]);
    
    int l = 1, r = N + 1;
    while(l < r - 1){
        int m = (l+r)/2;
        bool achou = false;
        for(int i = 0; i + m <= N; i++){
            int lg = __lg(m);
            int minimo = min(tabela[lg][i], tabela[lg][i + m - (1<<lg)]);
            if(minimo >= i + m)
                achou = true;
        }
        if(achou)
            l = m;
        else
            r = m;
    }
    cout<<l<<'\n';

    return 0;
}