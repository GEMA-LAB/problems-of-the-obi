#include <bits/stdc++.h>
using namespace std;

int main() {
  int dinheiro, num_frutas;
  cin >> dinheiro >> num_frutas;

  vector <pair<int, int>> fruta(num_frutas);
  for (int i = 0; i < num_frutas; i++) {
    // guarda na ordem (preço, tipo)
    cin >> fruta[i].second >> fruta[i].first;
  }
  // ordena por preço
  sort(fruta.begin(), fruta.end());

  // se já comprei fruta desse tipo
  vector <bool> comprei(101, false);
  int resp = 0;

  for (int i = 0; i < num_frutas; i++) {
    int tipo = fruta[i].second;
    int preco = fruta[i].first;
    if (comprei[tipo]) {
      // comprar tipo repetido é inútil
      continue;
    }
    if (preco > dinheiro) {
      // todos daqui pra frente vão ser mais caros do que meu dinheiro
      break;
    }
    // compro a fruta
    resp++;
    dinheiro -= preco;
    comprei[tipo] = true;
  }

  cout << resp << endl;
  return 0;
}
