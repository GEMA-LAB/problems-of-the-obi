// OBI2020
// emoticons

#include <cstdio>
#include <cstring>
using namespace std;

const int MAX = 180;
int main(void) {
  const char *divertido = ":-)";
  const char *chateado = ":-(";
  const char *prox;
  int num_divertido = 0;
  int num_chateado = 0;
  //string linha;

  char str[MAX+1];
  fgets (str, MAX, stdin);
  
  // conta número de :-)
  prox = str;
  while ((prox = strstr(prox, divertido)) != NULL) {
    num_divertido++;
    prox += 3;
  }   
  // conta número de :-(
  prox = str;
  while ((prox = strstr(prox, chateado)) != NULL) {
    num_chateado++;
    prox += 3;
  }   

  // imprime resultado
  if (num_divertido > num_chateado)
    printf("divertido\n");
  else if (num_divertido < num_chateado)
    printf("chateado\n");
  else
    printf("neutro\n");

  return 0;
}
