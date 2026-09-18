// OBI2022
// tarefa teste de redacao

#include<bits/stdc++.h>

using namespace std;

int n, m;
string letras = "abcdefghijklmnopqrstuvwxyz";

int main (void) {
  
  scanf ("%d%d", &n, &m);
  
  for (int i=1; i<=m; i++) {
    int x = i;
    while (x > 0) {
      printf("%c", (char) letras[x % 10]);
      x /= 10;
      printf(" ");
    }
  }
  
  printf("\n");
  return 0;
}
