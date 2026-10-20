#include <bits/stdc++.h>
int m[15][15];
int main() {
  int n; scanf("%d", &n);
  int i0, j0;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
      scanf("%d", &m[i][j]);
      if(m[i][j] == 0) {
        i0 = i;
        j0 = j;
      }
    }
      
  int i1 = 0;
  if(i0 == 0) i1 = 1;
  
  int soma0 = 0, soma1 = 0;
  for(int j = 0; j < n; j++) {
    soma0 += m[i0][j];
    soma1 += m[i1][j];
  }
  
  printf("%d\n", soma1 - soma0);
  printf("%d\n", i0 + 1);
  printf("%d\n", j0 + 1);
}
