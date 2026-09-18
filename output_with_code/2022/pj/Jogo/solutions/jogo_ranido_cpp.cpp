// OBI2022
// fase 3 - jogo
// r. anido

#include "bits/stdc++.h"
using namespace std;

int main(){
  int x, t;

  scanf("%d", &x);
  while (true) {
    scanf("%d", &t);
    if (t > x)
      printf("menor\n");
    else if (t < x)
      printf("maior\n");
    else {
      printf("correto\n");
      break;
    }
  }
  return 0;
}
