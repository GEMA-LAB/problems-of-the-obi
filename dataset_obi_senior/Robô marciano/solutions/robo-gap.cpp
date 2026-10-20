// Guilherme A. Pinto, OBI 2019, robo

#include <iostream>
#include <vector>
#include <queue>

#define MAX 1004

using namespace std;

typedef pair<int,int> pii;

int custo[MAX];
vector<bool> marca;
vector<pii> area[MAX];
priority_queue<pii,vector<pii>,greater<pii>> q;

int X1[MAX],Y1[MAX],X2[MAX],Y2[MAX];

int main(){
  int N;
  int Xi,Yi,Xf,Yf;
  
  cin >> Xi >> Yi >> Xf >> Yf;
  cin >> N;
  for ( int i = 0; i < N; i++ )
    cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];

  marca = vector<bool>(N+2,false);

  X1[N] = X2[N] = Xi;
  Y1[N] = Y2[N] = Yi;
  X1[N+1] = X2[N+1] = Xf;
  Y1[N+1] = Y2[N+1] = Yf;

  // monta o grafo, O(N^2)
  for ( int i = 0; i < N+1; i++ )
    for ( int j = i+1; j < N+2; j++ ){
      int dx = max(0, max(X1[i], X1[j]) - min(X2[i], X2[j]));
      int dy = max(0, max(Y1[i], Y1[j]) - min(Y2[i], Y2[j]));
      int c = dx + dy;

      area[i].push_back( {j,c} );
      area[j].push_back( {i,c} );
    }

  // Dijkstra  
  q.push( {0,N} );
  while ( not q.empty() ){
    auto p = q.top(); q.pop();
    int c = p.first;
    int a = p.second;
    if ( not marca[a] ){
      custo[a] = c;
      marca[a] = true;
      for ( auto e : area[a] ){
        int b = e.first;
        int d = e.second;
        if  ( not marca[b] )
          q.push( {c+d,b} );
      }
    }
  }
  
  cout << custo[N+1] << endl;
  return 0;
}
