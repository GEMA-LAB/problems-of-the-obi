// OBI2020
// fase 1 - garamana

#include <stdio.h>

#define MAX 101

char palavra1[MAX];
char palavra2[MAX];

int conta1[255];
int conta2[255];

int main () {
  scanf("%s%s", palavra1, palavra2);
  for (int i=0; i<25; i++) {
    conta1[i] = 0;
    conta2[i] = 0;
  }
  int i = 0;
  while (palavra1[i] != '\0') {
    conta1[(unsigned) palavra1[i] - (unsigned) 'a']++;
    if (palavra2[i] != '*')
      conta2[(unsigned) palavra2[i] - (unsigned) 'a']++;
    i++;
  }
  char resultado = 'S';
  for (int i=0; i<25; i++) {
    if (conta2[i] >  conta1[i]) {
      resultado = 'N';
      break;
    }
  }
  printf("%c\n",resultado);
}
