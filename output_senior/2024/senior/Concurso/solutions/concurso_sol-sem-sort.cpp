#include <bits/stdc++.h>

int main() {
  int n, k; scanf("%d%d", &n, &k);
  int v[n];
  for(int i = 0; i < n; i++) scanf("%d", &v[i]);
  for(int nota = 100; nota >= 1; nota--) {
    int cont = 0;
    for(int i = 0; i < n; i++)
      if(v[i] >= nota)
        cont++;
  
    if(cont >= k) {
      printf("%d\n", nota);
      break;
    }
  }
}