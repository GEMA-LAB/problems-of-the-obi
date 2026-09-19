#include<stdio.h>
#include<strings.h>

#define MAX 1000

char palavra[MAX+2];
int i, num_palavras, tot_palavras, compr, encontrou;
char letra;

int main(void) {
  num_palavras=0;
  tot_palavras=0;
  scanf("%c",&letra);
  while (scanf("%s",palavra)==1) {
    compr=strlen(palavra);
    encontrou=0;  // marca se encontrou a letra na palavra
    for (i=0; i<compr; i++)
      if (palavra[i]==letra)
	encontrou=1;
    num_palavras += encontrou;
    tot_palavras++;
  }
  printf("%.1f\n", 100.0*num_palavras/tot_palavras);
  return 0;
}
