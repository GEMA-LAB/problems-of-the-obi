#include <bits/stdc++.h>
int main() {
  int n; scanf("%d", &n);
  char s1[1010]; scanf(" %s", s1);
  int m; scanf("%d", &m);
  char s2[1010]; scanf(" %s", s2);
  
  int resp = 0;
  int i = 0;
  while(i < n && i < m) {
    if(s1[i] == s2[i]) resp++;
    else break;
    
    i++;
  }
  printf("%d\n", resp);
}