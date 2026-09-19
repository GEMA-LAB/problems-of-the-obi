#include <bits/stdc++.h>
#define MAX 300005

///Considere que a posicao inicial esta no (j,1)
///Querermos pegar todas as posicoes (j-k,k+1) para todo k>0
///Chamemos a altura de uma coluna anterior l de a[l]
///Essa coluna pode ser escolhida caso a[l]>=(j-l)+l
///Ou seja, caso a[l]+l>=j+1

int solve(std::vector<int> array){
    std::priority_queue<int,std::vector<int>,std::greater<int>> queue;
    int N = array.size();
    int ans = 0;
    for(int i=0; i!=N;i++){
        int valor = array[i]+i;
        queue.push(valor);
        while(queue.size()&&queue.top()<i+1){
            queue.pop();
        }
        ans=std::max(ans,(int)queue.size());
    }
    return ans;
}

int main()
{
    std::vector<int> array;
    int N;
    std::cin>>N;
    for(int i=0; i!= N; i++){
        int x;
        std::cin>>x;
        array.push_back(x);
    }
    int ans=solve(array);
    std::cout<<ans<<"\n";
}
