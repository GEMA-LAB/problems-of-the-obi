#include <bits/stdc++.h>

int main() {
  int d, a, n; scanf("%d %d %d", &d, &a, &n);
  int qtdDias = 31 - (n - 1);
  int aux = n - 1;
  if(n >= 16) aux = 15 - 1;
  int diaria = d + (a * aux);
  printf("%d\n", qtdDias * diaria);
}
