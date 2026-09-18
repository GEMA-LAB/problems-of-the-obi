#include <bits/stdc++.h>
#define MAX 105000
using ll = long long;
ll array[MAX];
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
        array[i]=x;
        if(i)
            array[i]+=array[i-1];
    }
    for(int i=0;i!=Q;++i){
        ll l,r;
        std::cin>>l>>r;
        std::cout<<(array[r-1]-(l>1?array[l-2]:0))*11LL*(r-l)<<"\n";
    }
}
