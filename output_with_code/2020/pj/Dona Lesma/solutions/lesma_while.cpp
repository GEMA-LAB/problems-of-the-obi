// OBI2020 - Fase 2
// dona lesma

#include <iostream>
using namespace std;

int main(void) {
  int altura, sobe, desce;

  cin >> altura >> sobe >> desce;

  int distancia = 0;
  int dias = 0;
  while (true) {
    dias = dias + 1;
    distancia = distancia + sobe;
    if (distancia >= altura)
      break;
    distancia = distancia - desce;
  }
  cout << dias << endl;

  return 0;
}
