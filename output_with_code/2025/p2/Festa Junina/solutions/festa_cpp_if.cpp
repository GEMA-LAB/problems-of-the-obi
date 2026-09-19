/*
  OBI 2025 - Fase 1
  Festa Junina
*/
#include <iostream>
using namespace std;

int main() {
  int e, s, l;
  cin >> e >> s >> l;

  int dist = 0;
  if (e < s) dist += s - e;
  else dist += e - s;
  if (e < l) dist += l - e;
  else dist += e - l;
  if (s < l) dist += l - s;
  else dist += s - l;

  cout << dist << endl;
  return 0;
}
