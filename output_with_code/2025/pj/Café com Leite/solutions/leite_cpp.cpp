/*
  OBI 2025 - Fase 1
  Cafe com Leite
*/
#include <iostream>
using namespace std;

int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  
  if (a <= c - d && c - d <= b) {
    cout << "S" << endl;
  } else {
    cout << "N" << endl;
  }
  return 0;
}
