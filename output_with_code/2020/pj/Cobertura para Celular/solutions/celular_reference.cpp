#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define sq(x) ((x)*(x))

int const MAX = 10010;

typedef long long ll;

ll X[MAX], Y[MAX], N, D;
vector<int> adj[MAX];
int marcado[MAX];

void dfs(int idx) {
  if(marcado[idx])return;
  marcado[idx] = 1;
  for(int i = 0; i < adj[idx].size(); i++)dfs(adj[idx][i]);
}

int main(){
  cin >> N;
  for(int i = 0; i < N; i++)
    cin >> X[i] >> Y[i];
  cin >> D;
  D *= D;
  for(int i = 0; i < N; i++){
    for(int j = i+1; j < N; j++){
      if(sq(X[i]-X[j])+sq(Y[i]-Y[j]) <= D){
	adj[i].push_back(j);
	adj[j].push_back(i);
      }
    }
  }
  memset(marcado,0,sizeof marcado);
  dfs(0);
  int ok = 1;
  for (int i = 0; i < N && ok; ok &= marcado[i++]);
  if (ok){
    cout << "S" << endl;
  }else{
    cout << "N" << endl;
  }
  return 0;
}
