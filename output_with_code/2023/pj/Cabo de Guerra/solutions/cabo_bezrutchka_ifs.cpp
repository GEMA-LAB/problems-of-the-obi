/**
 * OBI 2023 - Fase 3
 * Cabo de Guerra - Solução listando todos os casos
 * Mateus Bezrutchka
 **/
#include <iostream>
using namespace std;

int main() {
  int a, b, c, d, e, f;
  cin >> a >> b >> c >> d >> e >> f;
  
  bool resp = false;
  if (a + b + c == d + e + f) resp = true;
  if (a + b + d == c + e + f) resp = true;
  if (a + b + e == c + d + f) resp = true;
  if (a + b + f == c + d + e) resp = true;
  if (a + c + d == b + e + f) resp = true;
  if (a + c + e == b + d + f) resp = true;
  if (a + c + f == b + d + e) resp = true;
  if (a + d + e == b + c + f) resp = true;
  if (a + d + f == b + c + e) resp = true;
  if (a + e + f == b + c + d) resp = true;
  
  cout << (resp ? "S" : "N") << endl;
  return 0;
}
