#include <bits/stdc++.h>

int main()
{
    int bordas[4]={};
    int N;
    std::cin>>N;
    for(int i=0;i!=N;++i){
        for(int j=0;j!=N;++j){
            for(int k=0;k!=N;++k){
                int bd=0;
                if((!i)||i==N-1)++bd;
                if((!j)||j==N-1)++bd;
                if((!k)||k==N-1)++bd;
                ++bordas[bd];
            }
        }
    }
    for(int i=0;i!=4;++i){
        std::cout<<bordas[i]<<"\n";
    }
    //std::cout<<"\n";
}
