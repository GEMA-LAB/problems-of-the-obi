/*
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - modela os grupos de amigos como componentes conexas
      de um grafo. Faz DFS para identificar os grupos de amigos
    - usa vetor de marcação para ver se alguma componente
      aparece mais de uma vez em uma entrevista
*/

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2510;
int m[MAXN][MAXN], comp[MAXN], marc[MAXN], convidados[MAXN], presente[MAXN];
vector<int> grafo[MAXN];
void dfs(int v, int c) {
  marc[v] = 1;
  comp[v] = c;
  for(int i = 0; i < grafo[v].size(); i++) {
    int viz = grafo[v][i];
    if(marc[viz] == 0) dfs(viz, c);
  }
}
int main() {
  int n; scanf("%d", &n);
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++) {
      scanf(" %c", &m[i][j]);
    
      if(m[i][j] == '1')
        grafo[i].push_back(j);
    }
    
  int qtdComp = 0;
  for(int i = 1; i <= n; i++)
    if(marc[i] == 0) {
      qtdComp++;
      dfs(i, qtdComp);
    }
  
  int e; scanf("%d", &e);
  for(int i = 1; i <= e; i++) {
    int k; scanf("%d", &k);
    bool temAmigos = false;
    for(int j = 1; j <= k; j++) {
      scanf("%d", &convidados[j]);
      presente[comp[convidados[j]]]++;
      if(presente[comp[convidados[j]]] > 1) temAmigos = true;
    }
    
    if(temAmigos) printf("S\n");
    else printf("N\n");
    
    for(int j = 1; j <= k; j++) presente[comp[convidados[j]]]--;
  }
}