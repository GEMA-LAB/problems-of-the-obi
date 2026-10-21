/**
 * OBI 2023 - Fase 3
 * Balanceamento de Pirâmide - Solução listando todos os casos
 * Mateus Bezrutchka
 **/
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int a, b, c, d, e, f;
  cin >> a >> b >> c >> d >> e >> f;

  int soma = a + b + c + d + e + f;
  if (soma % 3 != 0) {
    // se a soma nao é divisivel por 3, é impossivel
    cout << "N" << endl;
    return 0;
  }

  // temos que achar um valor pro terceiro andar
  bool achei_3 = false;
  if (a == soma / 3) achei_3 = true;
  if (b == soma / 3) achei_3 = true;
  if (c == soma / 3) achei_3 = true;
  if (d == soma / 3) achei_3 = true;
  if (e == soma / 3) achei_3 = true;
  if (f == soma / 3) achei_3 = true;

  // agora temos que achar dois valores pro segundo andar
  // (observe que todos os numeros sao > 0, entao nunca usaremos
  // o mesmo valor usado pro achei_3)
  bool achei_2 = false;
  if (a + b == soma / 3) achei_2 = true;
  if (a + c == soma / 3) achei_2 = true;
  if (a + d == soma / 3) achei_2 = true;
  if (a + e == soma / 3) achei_2 = true;
  if (a + f == soma / 3) achei_2 = true;
  if (b + c == soma / 3) achei_2 = true;
  if (b + d == soma / 3) achei_2 = true;
  if (b + e == soma / 3) achei_2 = true;
  if (b + f == soma / 3) achei_2 = true;
  if (c + d == soma / 3) achei_2 = true;
  if (c + e == soma / 3) achei_2 = true;
  if (c + f == soma / 3) achei_2 = true;
  if (d + e == soma / 3) achei_2 = true;
  if (d + f == soma / 3) achei_2 = true;
  if (e + f == soma / 3) achei_2 = true;
  
  if (achei_3 && achei_2) {
    cout << "S" << endl;
  } else {
    cout << "N" << endl;
  }
  return 0;
}
