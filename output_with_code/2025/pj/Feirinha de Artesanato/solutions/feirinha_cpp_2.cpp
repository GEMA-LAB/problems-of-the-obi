#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
int preco[MAXN], tipo[MAXN], cliente[MAXN];
multiset<int> precos_para_tipo[MAXN];
multiset<pair<int, int>> todos_objetos;

int main() {
  int n, t = 2, c;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> tipo[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> preco[i];
  }
  cin >> c;
  for (int i = 0; i < c; i++) {
    cin >> cliente[i];
  }

  for (int i = 0; i < n; i++) {
    precos_para_tipo[tipo[i]].insert(preco[i]);
    todos_objetos.insert({preco[i], tipo[i]});
  }

  long long resp = 0;
  for (int i = 0; i < c; i++) {
    int tipo_atual = cliente[i];
    if (tipo_atual == 0) {
      // decide tipo para cliente indeciso
      auto iter_todos = todos_objetos.begin();
      if (iter_todos == todos_objetos.end()) continue;
      tipo_atual = (*iter_todos).second;
    }

    auto iter_tipo = precos_para_tipo[tipo_atual].begin();
    if (iter_tipo == precos_para_tipo[tipo_atual].end()) continue;
    int menor_preco = *iter_tipo;
    resp += menor_preco;

    precos_para_tipo[tipo_atual].erase(iter_tipo);
    pair<int, int> objeto = {menor_preco, tipo_atual};
    todos_objetos.erase(todos_objetos.find(objeto));
  }

  cout << resp << endl;
  return 0;
}
