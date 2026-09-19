/*
    OBI 2025 - Fase 3
    Forja de ORicalco
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;
const int logx = 30;

int get_pos( int r, int i, int k ){
    /*
        Seja j < i o maior indice tal que j = x*(k - 1) + r.

        Esta funcao retorna x.
    */

    if( i == -1 ) return -1;
    if( i%(k - 1) > r ) return i/(k - 1);
    return i/(k - 1) - 1;
}


int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, k; cin >> n >> k;

    // ultima ocorrencia de cada bit
    vector<int> last_occur(logx, -1);

    // para cada resto mod k - 1, um multiset para cada intervalo de OR diferente
    vector<vector<multiset<ll>>> ms(k - 1, vector<multiset<ll>>(logx + 1));
    vector<ll> dp(n + 1, inf);
    dp[0] = 0;

    ms[0][0].insert(0);

    // vector com os bits
    vector<int> bits(logx);
    iota( bits.begin(), bits.end(), 0 );

    for( int i = 1; i <= n; i++ ){
        int x; cin >> x;
        for( int j = 0; j < logx; j++ )
            if( x&(1<<j) )
                last_occur[j] = i;

        // ordenar os bits do mais recente para o mais antigo
        sort( bits.begin(), bits.end(), [&]( int i, int j ){
            return last_occur[i] > last_occur[j];
        });


        int OR = 0;

        // resto desejado
        int r = (i - 1)%(k - 1);
        int last_pos = get_pos(r, i, k);

        for( int j = 0; j < logx; j++ ){
            // Caso o multiset tenha mais intervalos do que deveria, passa para o proximo. 
            while( ms[r][j].size() > last_pos - get_pos(r, last_occur[bits[j]], k) ){
                int x = last_pos - (int)ms[r][j].size() + 1;
                int id = x*(k - 1) + r;

                ms[r][j].erase(ms[r][j].find(dp[id]));
                ms[r][j + 1].insert(dp[id]);
            }

            if( !ms[r][j].empty() )
                dp[i] = min( dp[i], *ms[r][j].begin() + OR );

            OR += (1<<bits[j]);
            last_pos = get_pos(r, last_occur[bits[j]], k);
        }

        if( !ms[r][logx].empty() )
            dp[i] = min( dp[i], *ms[r][logx].begin() + OR );

        ms[i%(k - 1)][0].insert(dp[i]);
    }

    cout << dp[n] << endl;
}

/*
    Obs: Os intervalos de cada possivel OR vao se deslocando para a direita com o tempo. 
    Por isso, cada dp pode mudar de multiset no maximo logx vezes

    A complexidade eh O(N*logx*logN)

    N*logx*logN = 100000*30*17 = 5.1*10^7
*/
