#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {FALSE = 0, TRUE} boolean;

void escreve_resultado(int naipe[13]) {
  boolean ok = TRUE;
  int falta = 0;
  for (int i=0; i<13; i++) {
    if (naipe[i] > 1) {
      ok = FALSE;
      break;
    }
    else if (naipe[i] == 0) {
      falta++;
    }
  }
  if (ok)
    printf("%d\n",falta);
  else
    printf("erro\n");
}
  
int main (void) {
  char linha[200];
  int copas[13], espadas[13], ouros[13], paus[13];
  int val;
  char naipe, tmp[3];
  
  scanf("%s", linha);

  for (int i=0; i<13; i++) {
    copas[i] = 0;
    espadas[i] = 0;
    ouros[i] = 0;
    paus[i] = 0;
  }
  for (int i=0; i<strlen(linha)/3; i++) {
    strncpy(tmp, &linha[i*3],2);
    tmp[2] = '\0';
    val = atoi(tmp) - 1;
    naipe = linha[i*3+2];
    if (naipe == 'C')
      copas[val]++;
    else if (naipe == 'E')
      espadas[val]++;
    else if (naipe == 'U')
      ouros[val]++;
    else
      paus[val]++;
  }

  // escreve resultado
  escreve_resultado(copas);
  escreve_resultado(espadas);
  escreve_resultado(ouros);
  escreve_resultado(paus);

  return 0;
}
