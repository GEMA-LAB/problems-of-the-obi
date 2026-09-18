// Guilherme A. Pinto, nota, OBI-2019

#include <bits/stdc++.h>
using namespace std;

// Solucao mais "otimizada": a rigor, nao precisa calcular as areas!
// Os triangulos das areas de Felix e Marzia sao iguais, portanto
// as areas se anulam na comparacao. Além disso, as alturas dos retangulos
// sao iguais, portanto basta comparar a base dos retangulos de Felix
// e Marzia.

int main(){
  int B,T;
  cin >> B >> T;

  int felix = min(B,T);      // base do retangulo de Felix
  int marzia = 160-max(B,T); // base do retangulo de Marzia

  if ( felix > marzia ) {
    cout << 1 << endl;
  } else {
    if ( felix < marzia ) {
      cout << 2 << endl;
    } else {
      cout << 0 << endl;
    }
  }

  return 0;
}
