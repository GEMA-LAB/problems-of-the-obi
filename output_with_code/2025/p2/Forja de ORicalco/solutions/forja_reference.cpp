/*
    OBI 2025 - Fase 3
    Forja de ORicalco
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll inf = 1e18;
const int logx = 30;

class Segtree{
    private:
        vector<ll> seg;
        int n;

        void update( int pos, int ini, int fim, int id, ll val ){
            if( ini > id || id > fim ) return;
            if( ini == fim ){ seg[pos] = val; return; }
            int l = 2*pos, r = 2*pos + 1, mid = ( ini + fim )/2;
            update( l, ini, mid, id, val ); update( r, mid + 1, fim, id, val );
            seg[pos] = min( seg[l], seg[r] );
        }

        ll query( int pos, int ini, int fim, int ki, int kf ){
            if( ki > fim || ini > kf ) return inf;
            if( ki <= ini && fim <= kf ) return seg[pos];
            int l = 2*pos, r = 2*pos + 1, mid = ( ini + fim )/2;
            return min( query( l, ini, mid, ki, kf ), query( r, mid + 1, fim, ki, kf ) );
        }
    public:
        Segtree( int n ) : n(n){
            seg.resize(4*(n + 1), inf);
        }

        void update(int id, ll val){
            update( 1, 0, n, id, val );
        }

        ll query( int l, int r ){
            return query( 1, 0, n, l, r );
        }
};

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

    // criar uma seg para cada resto mod k - 1, com tamanho teto(n/(k -1)) cada
    vector<Segtree> seg( k - 1, (n + k - 2)/(k - 1) );
    vector<ll> dp(n + 1, inf);

    dp[0] = 0;
    seg[0].update( 0, 0 );

    vector<int> bits(logx); 
    iota( bits.begin(), bits.end(), 0 ); 

    for( int i = 1; i <= n; i++ ){
        int x; cin >> x; 
        for( int j = 0; j < logx; j++ ) if( x&(1<<j) )
            last_occur[j] = i;
        
        // ordenar os bits do mais antigo para o mais recente
        sort( bits.begin(), bits.end(), [&]( int i, int j ){
            return last_occur[i] < last_occur[j];
        });


        ll OR = (1<<logx) - 1;
        int last_pos = -1;

        // resto desejado
        int r = (i - 1)%(k - 1);

        for( int bit : bits ){
            int pos = last_occur[bit];
            dp[i] = min( dp[i], seg[r].query( last_pos + 1, get_pos(r, pos, k) ) + OR );
            OR -= (1<<bit);
            last_pos = get_pos(r, pos, k);
        }
        dp[i] = min( dp[i], seg[r].query(last_pos + 1, get_pos(r, i, k) ) );

        seg[i%(k - 1)].update(i/(k - 1), dp[i]);
    }

    cout << dp[n] << endl;
}

/*
    Complexidade: O(N*logn*logx)
*/
