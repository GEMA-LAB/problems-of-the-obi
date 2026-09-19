#include <stdio.h>

#define ll long long

ll oo=1e9+1;
ll best[2][4][2], v[100001][4], pos[2][2];

int main(){

    ll n, ans=4*oo;
    scanf("%lld", &n);

    for(int i=0; i < 2; i++)
        for(int j=0; j < 4; j++)
            for(int k=0; k < 2; k++) best[i][j][k] = n;
    for(int i=0; i < 4; i++) v[n][i] = oo;

    for(int i=0; i < n; i++){
        ll t;
        scanf("%lld", &t);
        for(int j=0; j < 4; j++){ 
            scanf("%lld", &v[i][j]);
            ll f = v[best[t][j][0]][j], s = v[best[t][j][1]][j];
            if(f >= v[i][j]) best[t][j][1] = best[t][j][0], best[t][j][0] = i;
            else if(s >= v[i][j]) best[t][j][1] = i;
        }   
    }

    for(int i=0; i < 2; i++){
        for(int j=0; j < 4; j++){
            if(best[i][j][1] == n){
                printf("-1\n");
                return 0;
            }
        }
    }

    for(int aa=0; aa < 4; aa++){
        for(int bb=0; bb < 4; bb++){
            if(bb == aa) continue;
            for(int cc=0; cc < 4; cc++){
                if(cc == aa || cc == bb) continue;
                int dd = 6 - aa - bb - cc;
                int p[4] = {aa, bb, cc, dd};
                ll atual=0;
                for(int i=0; i < 2; i++) for(int j=0; j < 2; j++) pos[i][j] = 4;
                for(int i=0; i < 4; i++){
                    pos[p[i]&1][(p[i]/2)&1] = i;
                }
                for(int i=0; i < 2; i++){
                    ll p1[2] = {best[i][pos[i][0]][0], best[i][pos[i][0]][1]};
                    ll p2[2] = {best[i][pos[i][1]][0], best[i][pos[i][1]][1]}; 
                    if(p1[0] != p2[0]){
                        atual += v[p1[0]][pos[i][0]];
                        atual += v[p2[0]][pos[i][1]];
                    }
                    else{
                        ll a1, a2;
                        a1 = v[p1[0]][pos[i][0]] + v[p2[1]][pos[i][1]];
                        a2 = v[p1[1]][pos[i][0]] + v[p2[0]][pos[i][1]];
                        atual += (a1 < a2 ? a1 : a2);
                    }
                }
                if(atual < ans) ans = atual;
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}