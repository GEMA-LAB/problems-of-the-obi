// OBI-2019, onibus, O(TL), Guilherme A. Pinto

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> g;
vector<int> d;
queue<int> q;
int T,L,O,D;

// BFS
int bfs( int o ){
  d[o] = 0; // visitado, distancia zero
  q.push( o );

  while( not q.empty() ){
    int v = q.front(); q.pop();
    for ( int u: g[v] )
      if ( d[u] == -1 ){ // não visitado
        d[u] = d[v] + 1;
        if ( u == D ) return d[u];
        q.push( u );
      }
  }

  return -1; // não alcançável
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  int C,t;

  cin >> T >> L >> O >> D;

  g = vector<vector<int>>(T+L+1);
  d = vector<int>(T+L+1,-1);

  for( int i = 1; i <= L; i++ ){
    cin >> C;
    for( int j = 0; j < C; j++ ){
      cin >> t;
      g[t].push_back(i+T);
      g[i+T].push_back(t);
    }
  }

  cout << bfs(O)/2 << endl;

  return 0;
}