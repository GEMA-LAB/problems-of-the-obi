// Guilherme A. Pinto, OBI 2019, tabela

#include <iostream>
using namespace std;

int main(){

  int J,P,V,E,D;
  
  cin >> J >> P >> V >> E >> D;

  while ( (J == -1) or (P == -1) or (V == -1) or (E == -1) or (D == -1) ){

    // restricao J = V+E+D

    // 0 _ 1 1 1
    if ( J == -1 and ( V != -1 and E != -1 and D != -1 ) ){
      J = V+E+D;
    }
    // 1 _ 0 1 1
    if ( V == -1 and ( J != -1 and E != -1 and D != -1 ) ){
      V = J-E-D;
    }
    // 1 _ 1 0 1
    if ( E == -1 and ( J != -1 and V != -1 and D != -1 ) ){
      E = J-V-D;
    }
    // 1 _ 1 1 0
    if ( D == -1 and ( J != -1 and E != -1 and V != -1 ) ){
      D = J-E-V;
    }

    // restricao P = 3*V+E

    // _ 0 1 1 _
    if ( P == -1 and ( V != -1 and E != -1 ) ){
      P = 3*V+E;
    }
    // _ 1 0 1 _
    if ( V == -1 and ( P != -1 and E != -1 ) ){
      V = (P-E)/3;
    }
    // _ 1 1 0 _
    if ( E == -1 and ( P != -1 and V != -1 ) ){
      E = P-3*V;
    }

    // necessario combinar as duas restricoes
    if ( V == -1 and E == -1 ) {

      int K = J-D;

      // J-D = V+E = K =>
      // E = K-V => 
      // (P = 3V+E) => P = 3V+K-V =>
      // V = (P-K)/2
 
      V = (P-K)/2;
    }

    // nao pode ocorrer: J = -1 e D = -1
  }

  cout << J << " " << P << " " << V << " " << E << " " << D << endl;

  return 0;
}
