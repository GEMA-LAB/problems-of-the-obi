#include <bits/stdc++.h>
int main() {
  int n; scanf("%d", &n);
  char s[1010]; scanf(" %s", s);
  int qtd = 0;
  char last = '0';
  for(int i = 0; i < n; i++) {
    if(s[i] == last)
      qtd++;
    else {
      if(last != '0') printf(" %d %c", qtd, last);
      
      qtd = 1;
    }
    
    last = s[i];
  }
  printf(" %d %c\n", qtd, last);
}