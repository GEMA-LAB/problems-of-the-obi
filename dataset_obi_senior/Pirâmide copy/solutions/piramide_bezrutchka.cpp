/**
 * OBI 2023 - Fase 3
 * Balanceamento de Pirâmide - Solução com ordenação e força bruta
 * Mateus Bezrutchka
 **/
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  // lê numeros em um vetor e guarda a soma
  int v[6];
  int soma = 0;
  for (int i = 0; i < 6; i++) {
    cin >> v[i];
    soma += v[i];
  }

  // se a soma nao é divisivel por 3, é impossivel
  if (soma % 3 != 0) {
    cout << "N" << endl;
    return 0;
  }

  // o maior valor deve estar no terceiro andar
  sort(v, v + 6);
  if (v[5] != soma / 3) {
    cout << "N" << endl;
    return 0;
  }

  // temos que achar outros dois pro segundo andar
  for (int i = 0; i < 5; i++) {
    for (int k = i + 1; k < 5; k++) {
      if (v[i] + v[k] == soma / 3) {
        cout << "S" << endl;
        return 0;
      }
    }
  }

  // nao achamos par pro segundo andar
  cout << "N" << endl;
  return 0;
}
