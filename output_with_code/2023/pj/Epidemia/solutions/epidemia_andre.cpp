#include <bits/stdc++.h>
int main() {
  int n, r, p; scanf("%d %d %d", &n, &r, &p);
  int total = n;
  int dias = 0;
  while(total < p) {
    n = n * r;
    total += n;
    dias++;
  }
  printf("%d\n", dias);
}