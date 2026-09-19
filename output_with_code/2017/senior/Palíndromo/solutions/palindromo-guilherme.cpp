// Guilherme, OBI 2017

#include <iostream>
#include <cstring>
using namespace std;

#define MAX 2001

int dp[MAX];
int p[MAX][MAX];
string pal;

int palindromo( int a, int b ){
  if ( p[a][b] != -1 ) return p[a][b];
  if ( a == b ) return p[a][b] = 1;
  if ( a == b-1 ) return p[a][b] = (pal[a]==pal[b]);
  if ( pal[a] != pal[b] ) return p[a][b] = 0;
  return p[a][b] = palindromo( a+1, b-1 );
}

int menorParticao( int k ){
  if ( dp[k] != -1 ) return dp[k];
  if ( palindromo( 0, k ) == 1 ) return dp[k] = 1;
  int menor = MAX;
  for ( int i = k; i > 0; i-- )
    if ( palindromo( i, k ) == 1 ){
      int val = menorParticao( i-1 );
      if ( val + 1 < menor ) menor = val + 1;
    }
  return dp[k] = menor;
}

int main(){
  int N,res;

  memset( dp, -1, sizeof dp );
  memset( p, -1, sizeof p );

  cin >> N >> pal;
  cout << menorParticao( N-1 ) << endl;
 
  return 0;
}
