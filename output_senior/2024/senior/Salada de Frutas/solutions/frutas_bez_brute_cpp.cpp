#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101, MAXT = 101;
bool comprei[MAXT];  // se já comprei fruta desse tipo
int tipo[MAXN], preco[MAXN];

int main() {
  int dinheiro, num_frutas;
  cin >> dinheiro >> num_frutas;

  for (int i = 0; i < num_frutas; i++) {
    cin >> tipo[i] >> preco[i];
  }

  int resp = 0;

  while (true) {
    // procuro a melhor fruta pra comprar
    int mais_barata = -1;
    for (int i = 0; i < num_frutas; i++) {
      if (comprei[tipo[i]]) {
        // comprar tipo repetido é inútil
        continue;
      }
      if (mais_barata == -1 || preco[i] < preco[mais_barata]) {
        mais_barata = i;
      }
    }

    // vejo se já acabou o dinheiro
    if (mais_barata == -1 || preco[mais_barata] > dinheiro) {
      break;
    }

    // compro a fruta
    resp++;
    dinheiro -= preco[mais_barata];
    comprei[tipo[mais_barata]] = true;
  }

  cout << resp << endl;
  return 0;
}
