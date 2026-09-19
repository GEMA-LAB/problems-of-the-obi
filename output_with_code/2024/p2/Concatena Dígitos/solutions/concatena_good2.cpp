#include <bits/stdc++.h>
#define MAX 105000
using ll = long long;
ll pref[MAX][10];
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int N,Q;
    std::cin>>N>>Q;
    for(int i=0;i!=N;++i){
        int x;
        std::cin>>x;
        pref[i][x]++;
        if(i)
            for(int k=0;k<10;++k){
                pref[i][k]+=pref[i-1][k];
            }
    }
    for(int i=0;i!=Q;++i){
        int l,r;
        std::cin>>l>>r;
        --l;--r;
        ll ans=0;
        ll vals[10]={};
        for(int k=0;k!=10;++k){
            vals[k]=pref[r][k];
            if(l){
                vals[k]-=pref[l-1][k];
            }
        }
        for(int u=1;u!=10;++u){
            for(int v=1;v!=10;++v){
                if(u==v){
                    ans+=(11LL*u)*(((vals[u])*(vals[u]-1)));
                }else {
                    ans+=(10LL*u+v)*vals[u]*vals[v];
                }
            }
        }
        std::cout<<ans<<"\n";
    }
}
