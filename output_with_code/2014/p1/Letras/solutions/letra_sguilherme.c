/* Guilherme A. Pinto - OBI 2014 - Letra */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

char texto[MAXN+2];

int main() {
  char c,cc;
  int i, p, pc, n, flag;
  float freq;

  c = getchar(); getchar();
  
  i = 0;
  while ( (cc = getchar()) != '\n' ) texto[i++] = cc;  
  texto[i] = '\0'; n = i;

  for ( p = 1, pc = 0, flag = 1, i = 0; i < n; i++ ){
    if ( texto[i] == ' ' ){
      p++; flag = 1;
    }
    else {
      if ( texto[i] == c && flag ){
	pc++; flag = 0;
      }
    }
  } 

  freq = ((float)pc/(float)p)*100.0;
  printf("%.1f\n",freq);

  return 0;
}
