#include <bits/stdc++.h>
const int MAX = 1000010;
int juntos[MAX][2], separados[MAX][2], grupo[MAX];
int main() {
  int e, m, d;
  scanf("%d %d %d", &e, &m, &d);
  for(int i = 1; i <= m; i++)
    scanf("%d %d", &juntos[i][0], &juntos[i][1]);
  for(int i = 1; i <= d; i++)
    scanf("%d %d", &separados[i][0], &separados[i][1]);
  for(int i = 1; i <= e/3; i++) {
    int a, b, c; scanf("%d %d %d", &a, &b, &c);
    grupo[a] = grupo[b] = grupo[c] = i;
  }
  
  int resp = 0;
  for(int i = 1; i <= m; i++)
    if(grupo[juntos[i][0]] != grupo[juntos[i][1]])
      resp++;
  for(int i = 1; i <= d; i++)
    if(grupo[separados[i][0]] == grupo[separados[i][1]])
      resp++;
  printf("%d\n", resp);
}
