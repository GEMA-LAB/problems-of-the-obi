#include<bits/stdc++.h>

using namespace std;

int N, M, K;
vector<int> g[100005];
int R[100005];
int apoio[100005];
bool quebrado[100005];
bool retirado[100005];
bool tentar_retirar[100005];

int main (void) {
    cin>>N>>M>>K;
    for(int i = 0; i < M; i++){
        int a, b;
        cin>>a>>b;
        a--, b--;
        g[a].push_back(b);
        apoio[b]++;
    }
    for(int i = 0; i < K; i++){
        cin>>R[i];
        R[i]--;
        tentar_retirar[R[i]] = true;
    }
    for(int r = 0; r < K; r++){
        int i = R[r];
        queue<int> q;
        if(tentar_retirar[i] && !quebrado[i]){
            q.push(i);
            retirado[i] = true;
            while(!q.empty()){
                int v = q.front();
                q.pop();
                for(int u : g[v]){
                    apoio[u]--;
                    if(apoio[u] == 0 && !retirado[u]){
                        quebrado[u] = true;
                        q.push(u);
                    }
                }
            }
        }
    }
    
    int resposta = 0;
    for(int i = 0; i < N; i++)
        if(quebrado[i])
            resposta++;
    cout<<resposta<<endl;
}
