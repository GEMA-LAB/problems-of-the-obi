#include <bits/stdc++.h>
const int MAX = 510;
int estoque[MAX];
int main() {
  int n; scanf("%d", &n);
  for(int i = 1; i <= n; i++)
    scanf("%d", &estoque[i]);
  int p; scanf("%d", &p);
  int resp = 0;
  for(int i = 1; i <= p; i++) {
    int a; scanf("%d", &a);
    if(estoque[a] > 0) {
      resp++;
      estoque[a]--;
    }
  }
  printf("%d\n", resp);
}