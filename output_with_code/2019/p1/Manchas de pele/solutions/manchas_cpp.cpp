// OBI-2019, manchas, O(NM), linear na entrada, Guilherme A. Pinto

#include <iostream>
#include <queue>

#define MAX 1002

using namespace std;

int di[4] = {1,0,-1,0};
int dj[4] = {0,1,0,-1};

int m[MAX][MAX];
queue<pair<int,int>> q;
int N,M,cnt;

// BFS
void bfs( int i, int j ){
  m[i][j] = cnt;
  q.push( {i,j} );

  while( not q.empty() ){
    auto v = q.front(); q.pop();
    for ( int k = 0; k < 4; k++ ){
      int a = v.first + di[k];
      int b = v.second + dj[k];
      if ( m[a][b] == -1 ){
        m[a][b] = cnt;
        q.push( {a,b} );
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(false); cin.tie(0);

  cin >> M >> N;

  for( int i = 0; i <= M+1; i++ )
    for( int j = 0; j <= N+1; j++ )
      m[i][j] = 0;

  for( int i = 1; i <= M; i++ )
    for( int j = 1; j <= N; j++ ){
      int t;
      cin >> t;
      if ( t == 1 ) m[i][j] = -1;
    }

  cnt = 0;

  for( int i = 1; i <= M; i++ )
    for( int j = 1; j <= N; j++ )
      if ( m[i][j] == -1 ){
        cnt++;
        bfs( i, j );
      }

  cout << cnt << endl;

  return 0;
}