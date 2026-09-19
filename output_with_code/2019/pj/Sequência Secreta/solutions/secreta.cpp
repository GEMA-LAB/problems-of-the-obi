// Sequência secreta
// OBI2019
// R. Anido

#include <bits/stdc++.h>
using namespace std;

int n; 
int atual; // último valor marcado na sequência
int total; // total de valores marcados

int main(void) {
  int x;

  cin >> n;
  atual = -1;  //inicializa com um número diferente dos valores 1 e 2
  total = 0;  // total de números marcados

  for (int i=0; i<n; i++) {
    cin >> x;
    // cada vez que encontra um número diferente do 
    // último marcado, marca esse novo número
    if (atual != x) {
      atual = x;
      total += 1;
    }
  } 
  cout << total << endl;
  return(0);
}
