#include <bits/stdc++.h>
int soma(int v) {
  if(v == 0) return 0;
  return soma(v/10) + (v % 10);
}

int main() {
  int n, m, s; scanf("%d %d %d", &n, &m, &s);
  int resp = -1;
  for(int i = m; i >= n; i--) {
    if(soma(i) == s) {
      resp = i;
      break;
    }
  }
  printf("%d\n", resp);
}
