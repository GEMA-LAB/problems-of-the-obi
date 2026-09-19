#include <bits/stdc++.h>
using namespace std;
const long long int INF = 1e18;
const int LOG = 30;
const int MAXN = 100010;
const int MAXK = 100010;
vector<int> best[MAXK];
int ultimoIndiceDoBit[LOG];
long long int dp[MAXN];
int bits[LOG];
bool cmp(int bit1, int bit2) {
    return ultimoIndiceDoBit[bit1] < ultimoIndiceDoBit[bit2];    
}
int main(){
    int n, k; scanf("%d %d", &n, &k);

    for(int i = 0; i < LOG; i++) {
        ultimoIndiceDoBit[i] = -1;
        bits[i] = i;
    }

    dp[0] = 0;
    best[0].push_back(0);
    long long int ORtodos = 0;

    for(int i = 1; i <= n; i++){
        int atual; scanf("%d", &atual); 

        ORtodos = ORtodos | atual;
        for(int j = 0; j < LOG; j++) 
            if(atual&(1<<j))
                ultimoIndiceDoBit[j] = i;
        
        sort(bits, bits + LOG, cmp);
        
        dp[i] = dp[i - 1] + atual;    

        long long int OR = ORtodos;
        int lastPos = -1;
        int r = (i - 1)%(k - 1);
        int pos, aux, bestJ;
        for(int k = 0; k < LOG; k++){
            int bit = bits[k];
            pos = ultimoIndiceDoBit[bit];
            aux = lower_bound(best[r].begin(), best[r].end(), lastPos) - best[r].begin();
            if(aux < best[r].size()) {
                bestJ = best[r][aux];
                if(bestJ < pos) dp[i] = min(dp[i], dp[bestJ] + OR);    
            }

            if(OR & (1LL<<bit)) OR -= (1LL<<bit);
            lastPos = ultimoIndiceDoBit[bit];
        }

        int rcur = i%(k - 1);
        while(best[rcur].size() > 0 && dp[best[rcur].back()] > dp[i]) {
            best[rcur].pop_back();
        }
        best[rcur].push_back(i);
    }

    printf("%lld\n", dp[n]);
}
