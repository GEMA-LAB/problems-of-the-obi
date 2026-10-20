#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1e5 + 10;
int preco[MAXN], tipo[MAXN], cliente[MAXN];

// {{preco, tipo}, indice}
typedef pair<pair<int, int>, int> obj;
vector<obj> todos_objetos;
vector<obj> precos_para_tipo[MAXN];

bool usado[MAXN];
// pos[0] -- ponteiro dos indecisos em todos_objetos
// pos[t] -- ponteiro dos decididos em precos_para_tipo[t]
int pos[MAXN];

int main() {
  int n, t, c;
  cin >> n >> t;
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
    obj cur_obj = {{preco[i], tipo[i]}, i};
    precos_para_tipo[tipo[i]].push_back(cur_obj);
    todos_objetos.push_back(cur_obj);
  }

  for (int i = 1; i <= t; i++) {
    sort(precos_para_tipo[i].begin(), precos_para_tipo[i].end());
  }
  sort(todos_objetos.begin(), todos_objetos.end());

  long long resp = 0;
  for (int i = 0; i < c; i++) {
    int u = cliente[i];
    obj cur_obj = {{-1, -1}, -1};
    if (u == 0) {
      while (pos[0] < n) {
        cur_obj = todos_objetos[pos[0]];
        if (!usado[cur_obj.second]) break;
        pos[0]++;
      }
    } else {
      while (pos[u] < (int) precos_para_tipo[u].size()) {
        cur_obj = precos_para_tipo[u][pos[u]];
        if (!usado[cur_obj.second]) break;
        pos[u]++;
      }
    }
    if (cur_obj.second == -1 || usado[cur_obj.second]) continue;
    usado[cur_obj.second] = true;
    resp += cur_obj.first.first;
  }

  cout << resp << endl;
  return 0;
}
