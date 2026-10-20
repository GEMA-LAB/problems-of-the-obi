#include <bits/stdc++.h>
using ll = long long;
typedef std::pair<int,int> pii;
typedef std::pair<pii,pii> ppp;
typedef std::pair<ll,pii> plp;
int N,M;
std::vector<std::vector<ll>> vec,answer;
std::vector<std::vector<pii>> pai;
std::vector<std::vector<ll>> poder;
pii find(pii a){
    auto& q = pai[a.first][a.second];
    if(q==a)
        return a;
    return q=find(q);
}
void Union(pii a,pii b){
    a=find(a);b=find(b);
    if(a!=b){
        if(poder[a.first][a.second]>poder[b.first][b.second])std::swap(a,b);
        pai[a.first][a.second]=b;
        poder[b.first][b.second]+=poder[a.first][a.second];
    }
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    ///Guarda as queries de perguntas
    std::map<ll,std::vector<pii>> queries_ask;
    ///Guarda as queries de conexao
    std::map<ll,std::vector<ppp>> queries_connect;
    ///Guarda os momentos das queries
    std::set<ll> eventos;
    std::cin>>N>>M;
    ///Le input
    for(int i=0;i!=N;++i){
        std::vector<ll> linha;
        for(int j=0;j!=M;++j){
            int x;
            std::cin>>x;
            ///Prepara queries iniciais
            queries_ask[x].push_back({i,j});
            eventos.insert(x);
            linha.push_back(x);
        }
        vec.push_back(linha);
    }
    ///Cria arestas
    for(int i=0;i!=N;++i){
        for(int j=0;j!=M;++j){
            ll loc = vec[i][j];
            if(j){
                ll p2 = vec[i][j-1];
                ll tot = std::max(p2,loc);
                eventos.insert(tot);
                queries_connect[tot].push_back({{i,j},{i,j-1}});
            }
            if(i){
                ll p2 = vec[i-1][j];
                ll tot = std::max(p2,loc);
                eventos.insert(tot);
                queries_connect[tot].push_back({{i,j},{i-1,j}});
            }
            if(j+1!=M){
                ll p2 = vec[i][j+1];
                ll tot = std::max(p2,loc);
                eventos.insert(tot);
                queries_connect[tot].push_back({{i,j},{i,j+1}});
            }
            if(i+1!=N){
                ll p2 = vec[i+1][j];
                ll tot = std::max(p2,loc);
                eventos.insert(tot);
                queries_connect[tot].push_back({{i,j},{i+1,j}});
            }
        }
    }
    ///Monta DSU
    answer=vec;
    for(int i=0;i!=N;++i){
        std::vector<pii> linhapai;
        std::vector<ll> linhapoder;
        for(int j=0;j!=M;++j){
            linhapai.push_back({i,j});
            linhapoder.push_back(vec[i][j]);
        }
        pai.push_back(linhapai);
        poder.push_back(linhapoder);
    }
    ///Processa queries
    while(eventos.size()){
        ll time = *eventos.begin();
        eventos.erase(eventos.begin());
        for(auto&y:queries_connect[time]){
            Union(y.first,y.second);
        }
        for(auto&y:queries_ask[time]){
            pii p = find(y);
            ll pd = poder[p.first][p.second];
            if(pd>time){
                queries_ask[pd].push_back(y);
                eventos.insert(pd);
            }else {
                answer[y.first][y.second]=pd;
            }
        }
    }
    ///Imprime resposta
    for(int i=0;i!=N;++i){
        for(int j=0;j!=M;++j){
            if(j>0) std::cout<<" ";
            std::cout<<answer[i][j];
        }
        std::cout<<"\n";
    }
}
