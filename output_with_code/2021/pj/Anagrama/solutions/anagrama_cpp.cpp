// OBI2021 - Fase 2
// Anagrama

#include <bits/stdc++.h>
using namespace std;

vector<char> letras1, letras2;

int main(void) {
  int n;
  string linha;

  // usando scanf para remover da entrada o final de linha após o valor de n
  scanf("%d\n", &n);
  getline(cin, linha);
  for (char c:linha)
    if (c != ' ' && c != ',' && c != '.')
	letras1.push_back(c);

  getline(cin, linha);
  for (char c:linha)
    if (c != ' ' && c != ',' && c != '.')
	letras2.push_back(c);

  char res = 'S';
  if (letras1.size() != letras2.size()) {
    res = 'N';
  }
  else {
    sort(letras1.begin(), letras1.end());
    sort(letras2.begin(), letras2.end());
    for (int i=0; i<letras1.size(); i++) {
      if (letras1[i] != letras2[i]) {
	res = 'N';
	break;
      }
    }
  }
  cout << res << endl;
}
