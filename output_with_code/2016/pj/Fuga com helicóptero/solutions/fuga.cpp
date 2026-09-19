// Guilherme A. Pinto, 2016

#include <iostream>

using namespace std;

int main(){
  int H,P,F,D;

  cin >> H >> P >> F >> D;

  // simula o movimento do fugitivo ate
  // encontrar o policial ou o helicoptero
  while( F != H && F != P ){
    F += D;
    if ( F < 0 ) F = 15;
    if ( F > 15 ) F = 0;
  }

  if ( F == H ) cout << "S" << endl;
  else cout << "N" << endl;
  
  return 0;
}
