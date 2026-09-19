#include<bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int n; cin>>n;
    vector<string> topico(n);
    map<string, int> topico_da_palavra;
    for(int i=0; i<n; i++){
        cin>>topico[i];
        int k;
        cin>>k;
        while(k--){
            string palavra;
            cin>>palavra;
            topico_da_palavra[palavra] = i;
        }
    }
    vector<int> relacionadas(n);
    int x;
    cin>>x;
    int maximo = 0;
    string resposta = "";
    while(x--){
        string p;
        cin>>p;
        if(!topico_da_palavra.count(p))
            continue;
        int t = topico_da_palavra[p];
        relacionadas[t]++;
        if(relacionadas[t] > maximo){
            maximo = relacionadas[t];
            resposta = topico[t];
        } else if(relacionadas[t] == maximo && topico[t] < resposta){
            resposta = topico[t];
        }
    }
    cout<<resposta<<'\n';

    return 0;
}