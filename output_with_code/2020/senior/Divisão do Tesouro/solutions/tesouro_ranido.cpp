// OBI2020
// tesouro

#include <cstdio>
using namespace std;

int moedas,marinheiros;
int parte, capitao;

int main (void) {
  
  scanf("%d%d", &moedas, &marinheiros);
  capitao = 2;
  parte = moedas/(marinheiros+capitao);
  printf("%d\n", 2*parte);
}
