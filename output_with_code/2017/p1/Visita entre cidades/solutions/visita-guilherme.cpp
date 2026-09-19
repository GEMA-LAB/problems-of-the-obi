// Guilherme A. Pinto, OBI 2017, visita

#include <iostream>
#include <vector>

#define MAX 10001

using namespace std;

vector<pair<int,int>> g[MAX];
int N, A, B;

bool dfs( int atual, int pai, int dist, int destino ){

  if ( atual == destino ){
    cout << dist << endl;
    return true;
  }
  
  for ( auto p : g[atual] ){
    int c = p.first;
    int d = p.second;
    if ( c != pai )
      if ( dfs( c, atual, dist + d, destino ) )
	return true;
  }
    
  return false;
}

int main(){
  int P, Q, D;
  
  cin >> N >> A >> B;
  for ( int i = 1; i <= N-1; i++ ){
    cin >> P >> Q >> D;
    g[P].push_back( {Q,D} );
    g[Q].push_back( {P,D} );
  }
  
  dfs( A, -1, 0, B );
  
  return 0;
}
