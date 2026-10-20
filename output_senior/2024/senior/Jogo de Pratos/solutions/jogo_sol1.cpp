#include <bits/stdc++.h>
#define MAX 55
int main()
{
    int mat[MAX][MAX]={};
    int N,Q;
    std::cin>>N>>Q;
    for(int i=1;i<=N;++i){
        std::string s;
        std::cin>>s;
        for(int j=1;j<=N;++j){
            if(s[j-1]=='1'){
                mat[i][j]=1;
            }
        }
    }
    for(int __=0;__!=Q;++__){
        int viz[MAX][MAX]={};
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                viz[i][j]+=mat[i+1][j];
                viz[i][j]+=mat[i-1][j];
                viz[i][j]+=mat[i+1][j+1];
                viz[i][j]+=mat[i-1][j-1];
                viz[i][j]+=mat[i+1][j-1];
                viz[i][j]+=mat[i-1][j+1];
                viz[i][j]+=mat[i][j+1];
                viz[i][j]+=mat[i][j-1];
            }
        }
        for(int i=1;i<=N;++i){
            for(int j=1;j<=N;++j){
                if(mat[i][j]){
                    if(viz[i][j]<2||viz[i][j]>3){
                        mat[i][j]=0;
                    }
                }else {
                    if(viz[i][j]==3){
                        mat[i][j]=1;
                    }
                }
            }
        }
    }
    for(int i=1;i<=N;++i){
        for(int j=1;j<=N;++j){
            std::cout<<(char)('0'+mat[i][j]);
        }
        std::cout<<"\n";
    }
}
