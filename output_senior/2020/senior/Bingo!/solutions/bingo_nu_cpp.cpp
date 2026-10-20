// Guilherme A. Pinto, OBI 2020, bingo, O(NU)

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> cartelas; // cartelas[n]: cartelas contendo numero n, em ordem
vector<int> cnt; // cnt[c]: quantos numeros ja marcados na cartela c
vector<int> vencedores; // cartelas vencedoras, em ordem

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  
  int N, K, U, n;

  cin >> N >> K >> U;

  cnt = vector<int>( N+1, 0 );
  cartelas = vector<vector<int>>( U+1 );

  for ( int c = 1; c <= N; c++ )
    for ( int j = 1; j <= K; j++ ){
      cin >> n;
      cartelas[n].push_back( c );
    }

  for ( int i = 1; i <= U and vencedores.size() == 0; i++ ){
    cin >> n;
    for ( int c: cartelas[n] )
      if ( ++cnt[c] == K ) vencedores.push_back( c );
  }

  string s = "";
  for ( int c : vencedores ){
    cout << s << c;
    s = " ";
  }
  cout << endl;

  return 0;
}
