// OBI2022 - Fase 2
// Tarefa Troféu
// André Sousa


#include <bits/stdc++.h>

int main() {
  int n1, n2, n3, n4, n5;
  scanf("%d %d %d %d %d", &n1, &n2, &n3, &n4, &n5);
  
  int maior = n1;
  int maior2 = -1;
  if(n2 != maior)
    maior2 = n2;
  else if(n3 != maior)
    maior2 = n3;
  else if(n4 != maior)
    maior2 = n4;
  else if(n5 != maior)
    maior2 = n5;
  
  int t = 1;
  if(n2 == maior) t++;
  if(n3 == maior) t++;
  if(n4 == maior) t++;
  if(n5 == maior) t++;
  
  int p = 0;
  if(n2 == maior2) p++;
  if(n3 == maior2) p++;
  if(n4 == maior2) p++;
  if(n5 == maior2) p++;
  
  printf("%d %d\n", t, p);
}
