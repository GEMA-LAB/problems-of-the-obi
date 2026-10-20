/*
  OBI 2025 - Fase 1
  Cafeteria
*/
#include <iostream>
using namespace std;

int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  bool possivel = false;

  // testa todas as quantidades de doses
  for (int doses = 1; doses * d <= c; doses++) {
    int leite = c - doses * d;
    if (a <= leite && leite <= b) {
      possivel = true;
    }
  }

  if (possivel) {
    cout << "S" << endl;
  } else {
    cout << "N" << endl;
  }
  return 0;
}
