// OBI2022
// fase 3 - caravana
// r. anido

#include "bits/stdc++.h"
using namespace std;

int main(){
  int n;
  vector<int> pesos;
  int soma = 0;

  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    int p;
    scanf("%d", &p);
    soma += p;
    pesos.push_back(p);
  }

  int ideal = soma / n;
  for (int i=0; i<n; i++) {
    printf("%d\n", ideal - pesos[i]);
  }
  
  return 0;
}
