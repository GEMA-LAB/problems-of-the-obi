#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100100;
int posicao_no_ranking[MAXN];

int main() {
  int n;
  cin >> n;
  for (int posicao = 1; posicao <= n; posicao++) {
    int atleta;
    cin >> atleta;
    posicao_no_ranking[atleta] = posicao;
  }

  for (int atleta = 1; atleta <= n; atleta++) {
    cout << posicao_no_ranking[atleta] << endl;
  }
  return 0;
}
