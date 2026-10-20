#include <bits/stdc++.h>
using namespace std;
//Mega-sanduíche solucao parcial com backtracking
const int MAXN = 55;
int n, m;
vector<int> grafo[MAXN];
long long int resp = 0;

int marc[MAXN];
void backtracking(int v, int pegos) {
    if(v == n + 1) {
        if(pegos > 0) resp++;
        return;
    }
    
    //testando nao pegar v
    backtracking(v + 1, pegos);
    
    //testando pegar v
    bool posso = true;
    for(int i = 0; i < grafo[v].size(); i++) {
        int viz = grafo[v][i];
        if(marc[viz] == 1) posso = false;
    }
    if(posso) {
        marc[v] = 1;
        backtracking(v + 1, pegos + 1);
        marc[v] = 0;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d %d", &a, &b);
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    backtracking(1, 0);
    printf("%lld\n", resp);
    return 0;
}
