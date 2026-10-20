// OBI2020
// fase 1 - garamana

#include <bits/stdc++.h>
using namespace std;
const int MAX = 101;

char palavra1[MAX];
char palavra2[MAX];
map<char,int> letras;

int main () {
  scanf("%s%s", palavra1, palavra2);
  int i = 0;
  while (palavra1[i] != '\0') {
    letras[palavra1[i]]++;
    if (palavra2[i] != '*')
      letras[palavra2[i]]--;
    i++;
  }
  char resultado = 'S';
   for(conste auto &[k, v] : letras)
     if (v < 0) {
       resultado = 'N';
       break;
     }
  printf("%c\n",resultado);
}
