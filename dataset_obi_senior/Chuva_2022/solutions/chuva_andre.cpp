#include <bits/stdc++.h>
const int MAXS = 1000010;
int marc[MAXS];

int main() {
  int n, s; scanf("%d %d", &n, &s);
  int soma = 0;
  marc[0] = 1;
  long long int resp = 0;

  for(int i = 1; i <= n; i++) {
    int v; scanf("%d", &v);
    soma += v;
    if(soma - s >= 0) resp += marc[soma - s];
    marc[soma]++;
  }

  printf("%lld\n", resp);
}
