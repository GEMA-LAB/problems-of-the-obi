/**
 * OBI 2023 - Fase 3
 * Balanceamento de Pirâmide - Solução força-bruta testando todas as permutações
 * Mateus Bezrutchka
 **/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  vector <int> x;
  x.resize(6);
  for (int i = 0; i < 6; i++) {
    cin >> x[i];
  }

  sort(x.begin(), x.end());
  while (1) {
    if (x[0] + x[1] + x[2] == x[5] && x[3] + x[4] == x[5]) {
      cout << "S" << endl;
      return 0;
    }
    if (!next_permutation(x.begin(), x.end())) break;
  }
  
  cout << "N" << endl;
  return 0;
}
