// Guilherme A. Pinto, OBI-2016, medalhas

#include <bits/stdc++.h>

using namespace std;

struct nadador {
  int tempo, numero;
  bool operator<(const nadador& o) const { return (tempo < o.tempo); }
};

nadador v[4];

int main() {

  v[0].tempo = v[0].numero = 0;

  for ( int i = 1; i <= 3; i++ ){
    scanf( "%d", &v[i].tempo );
    v[i].numero = i;
  }

  sort( v, v + 4 );

  for ( int i = 1; i <= 3; i++ ) printf( "%d\n", v[i].numero );
  
  return 0;
}
