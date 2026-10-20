#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  string instrucoes;
  cin >> instrucoes;

  int sala = 1;

  // passa pelas instruções em ordem, atualizando a sala a cada passo
  for (char instrucao : instrucoes) {
    if (instrucao == 'E') {
      sala = 2 * sala;
    } else {
      sala = 2 * sala + 1;
    }
  }

  cout << sala << endl;
  return 0;
}
