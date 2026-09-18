/*
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - define o representante de cada grupo de amigos
      como o menor ID no grupo
    - usa vetor de marcação para ver se algum representante
      aparece mais de uma vez em uma entrevista
*/

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2510;
int m[MAXN][MAXN], menorAmigo[MAXN], convidados[MAXN], presente[MAXN];

int main() {
  int n; scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    menorAmigo[i] = i;
    for(int j = 1; j <= n; j++) {
      scanf(" %c", &m[i][j]);
    
      if((m[i][j] == '1') && (j < menorAmigo[i])) menorAmigo[i] = j;
    }
  }
  
  int e; scanf("%d", &e);
  for(int i = 1; i <= e; i++) {
    int k; scanf("%d", &k);
    bool temAmigos = false;
    for(int j = 1; j <= k; j++) {
      scanf("%d", &convidados[j]);
      presente[menorAmigo[convidados[j]]]++;
      if(presente[menorAmigo[convidados[j]]] > 1) temAmigos = true;
    }
    
    if(temAmigos) printf("S\n");
    else printf("N\n");
    
    for(int j = 1; j <= k; j++) presente[menorAmigo[convidados[j]]]--;
  }
}