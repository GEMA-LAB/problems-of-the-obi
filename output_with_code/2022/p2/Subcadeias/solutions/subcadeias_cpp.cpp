#include<bits/stdc++.h>
using namespace std;
const int MAXN = 510;
char c[MAXN];

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) scanf(" %c", &c[i]);
  
  int resp = 1;
  for(int ini = 0; ini < n; ini++) {
    for(int fim = ini; fim < n; fim++) {
      bool ispal = true;
      for(int k = ini; k <= fim; k++) {
        if(c[k] != c[ini + fim - k]) ispal = false;
      }
      
      if(ispal) resp = max(resp, fim - ini + 1);
    }
  }
  
  printf("%d\n", resp);
}
