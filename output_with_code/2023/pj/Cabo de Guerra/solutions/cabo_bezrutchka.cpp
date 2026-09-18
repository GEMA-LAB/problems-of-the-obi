/**
 * OBI 2023 - Fase 3
 * Cabo de Guerra - Solução força-bruta com loops
 * Mateus Bezrutchka
 **/
#include <iostream>
using namespace std;

int main() {
  // le os 6 valores em um vetor, guardando a soma total
  int x[7];
  int soma = 0;
  for (int i = 1; i <= 6; i++) {
    cin >> x[i];
    soma += x[i];
  }

// se a soma for impar, é impossivel dividir igual
  if (soma % 2 == 1) {
    cout << "N" << endl;
    return 0;
  }

  int meia_soma = soma / 2;
  // precisamos encontrar (i,k) tal que a tripla (1,i,k) pode ser um time;
  // testamos todas as possibilidades
  for (int i = 2; i <= 6; i++) {
    for (int k = i + 1; k <= 6; k++) {
      if (meia_soma == x[1] + x[i] + x[k]) {
        // encontramos, ja podemos terminar o programa
        cout << "S" << endl;
        return 0;
      }
    }
  }

  // se chegamos aqui, nao encontramos solucao
  cout << "N" << endl;
  return 0;
}
