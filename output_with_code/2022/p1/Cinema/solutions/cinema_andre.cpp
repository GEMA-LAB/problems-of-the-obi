#include <bits/stdc++.h>
int preco(int idade) {
  if(idade <= 17) return 15;
  if(idade <= 59) return 30;
  return 20;
}
int main() {
  int a, b; scanf("%d %d", &a, &b);
  printf("%d\n", preco(a) + preco(b));
}
