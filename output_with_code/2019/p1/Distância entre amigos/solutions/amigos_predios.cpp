// Guilherme A. Pinto, predios, OBI-2019
// O(N), diametro de arvore

// Cada andar eh um vertice. Arestas entre andares adjacentes
// no mesmo predio e entre andares terreos de predios adjacentes.
// A arvore nao precisa (nao deve!) ser construida explicitamente

#include <bits/stdc++.h>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;

  vector<int> p = vector<int>(N);
  
  for( int i = 0; i < N; i++ )
    cin >> p[i];
  
  // indice k do predio cujo ultimo andar e o mais distante
  // do ultimo andar do predio 0

  int d0max = 0;
  int k = -1;
  for( int i = 1; i < N; i++ ) {
    int d0i = p[0]+(i)+p[i];
    if ( d0i > d0max ) {
      d0max = d0i;
      k = i;
    }
  }

  // distancia maxima a partir do ultimo andar do predio k
  
  int dkmax = 0;
  for( int i = 0; i < N; i++ ) 
    if ( i != k ) 
      dkmax = max( dkmax, p[k]+(abs(k-i))+p[i] );

  cout << dkmax << endl;
  
  return 0;
}
