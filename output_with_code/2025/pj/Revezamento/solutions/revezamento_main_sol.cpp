#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const long long int inf = 1e9 +5;

ii melhores_tempos[2][4][2];

int main(){

    int n;
    cin >> n;
    
    for(int i=0; i<2; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<2; k++){
                melhores_tempos[i][j][k] = {(ll) inf, (ll) inf};
            }
        }
    }

    int meninos = 0;
    
    for(int i=0; i<n; i++){
        int modalidade;
        cin >> modalidade;
        meninos += modalidade;

        for(int estilo =0; estilo <4; estilo++){
            ll tempo_estilo;
            cin >> tempo_estilo;

            if(tempo_estilo <= melhores_tempos[modalidade][estilo][0].second){

                melhores_tempos[modalidade][estilo][1] = melhores_tempos[modalidade][estilo][0];
                melhores_tempos[modalidade][estilo][0] = {i, tempo_estilo};
            }
            else if(tempo_estilo <= melhores_tempos[modalidade][estilo][1].second){
                melhores_tempos[modalidade][estilo][1] = {i, tempo_estilo};
            }
        }
    }

    if(meninos < 2 || (n-meninos) < 2){
        cout << -1 << endl;
        return 0;
    }

    vector<int> combinacao = {0,1,2,3};

    ll menor = -1;

    do{

        int f1 = combinacao[0], f2 = combinacao[1], m1 = combinacao[2], m2 = combinacao[3];

        ll f_total = 0;
        if(melhores_tempos[0][f1][0].first != melhores_tempos[0][f2][0].first){
            f_total += (melhores_tempos[0][f1][0].second + melhores_tempos[0][f2][0].second);
        }
        else{
            int aux1 = melhores_tempos[0][f1][0].second + melhores_tempos[0][f2][1].second;
            int aux2 = melhores_tempos[0][f1][1].second + melhores_tempos[0][f2][0].second;
            f_total = min(aux1, aux2);
        }

        ll m_total = 0;
        if(melhores_tempos[1][m1][0].first != melhores_tempos[1][m2][0].first){
            m_total = melhores_tempos[1][m1][0].second + melhores_tempos[1][m2][0].second;
        }
        else{
            int aux1 = melhores_tempos[1][m1][0].second + melhores_tempos[1][m2][1].second;
            int aux2 = melhores_tempos[1][m1][1].second + melhores_tempos[1][m2][0].second;
            m_total = min(aux1, aux2);
        }

        if(menor == -1 or menor >= f_total + m_total) menor = f_total + m_total;
        
    }while(next_permutation(combinacao.begin(), combinacao.end()));

    cout << menor << endl;
    return 0;
}
