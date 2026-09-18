// OBI2021 - Fase 2
// Pesquisa de preços

#include <bits/stdc++.h>

using namespace std;

int n;
string estado;
float alcool, gasolina;
bool existe = false;

int main(void) {
  cin >> n;
  for (int i=0; i<n; i++) {
    cin >> estado >> alcool >> gasolina;
    if (alcool/gasolina <= 0.70) {
      cout << estado << endl;
      existe = true;
    }
  }

  // se não imprimiu nenhum estado, imprime asterisco
  if (!existe)
    printf("*\n");

  return 0;
}
