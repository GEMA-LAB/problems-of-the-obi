// OBI-2019, xadrez, Guilherme A. Pinto

#include <iostream>

using namespace std;

int main(){
  int N, T;

  cin >> N >> T;

  if ( T == 0 ) cout << N << endl;
  if ( T == 1 ) cout << N*(N-1) << endl; // combinação de N dois a dois, vezes dois (por quê?)
  if ( T == 2 ) cout << (N*(N-1)*(N-2))/6 << endl; // combinação de N três a três (por quê?)

  return 0;
}