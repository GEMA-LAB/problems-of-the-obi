#include <bits/stdc++.h>
using namespace std;

int main() {
  int d;
  cin >> d;

  // divisão inteira arredonda pra baixo
  int ponto_antes = (d / 400) * 400;
  int dist_antes = d - ponto_antes;

  int ponto_depois = ponto_antes + 400;
  int dist_depois = ponto_depois - d;

  cout << min(dist_antes, dist_depois) << endl;
  return 0;
}
