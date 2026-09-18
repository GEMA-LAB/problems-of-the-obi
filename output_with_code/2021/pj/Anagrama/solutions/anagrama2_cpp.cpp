// OBI2021 - Fase 2
// Anagrama

#include <bits/stdc++.h>
using namespace std;

int letras1[26];
int letras2[26];

int main(void) {
  int n;
  string linha;

  // usando scanf para remover da entrada o final de linha após o valor de n
  scanf("%d\n", &n);
  getline(cin, linha);
  for (char c:linha)
    if (c != ' ' && c != ',' && c != '.')
      letras1[int(c - 'a')]++;

  getline(cin, linha);
  for (char c:linha)
    if (c != ' ' && c != ',' && c != '.')
      letras2[int(c - 'a')]++;

  char res = 'S';
  for (int i=0; i<26; i++) {
      if (letras1[i] != letras2[i]) {
	cout << 'N' << endl;
	return 0;
      }
  }
  cout << 'S' << endl;
}
