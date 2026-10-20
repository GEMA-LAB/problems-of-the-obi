// torre de dados
// obi2020 - fase 3

#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 10000

int n;
int dado[MAX][6];
int lado[6] = {5, 3, 4, 1, 2, 0};

int max_lado(int n, int top)
{
  int bottom = lado[top];
  int max=0;
  for (int i=0; i<6; i++) {
    if (i==top || i==bottom) continue;
    if (max < dado[n][i])
      max = dado[n][i];
  }
  return max;
}

int encontra(int n, int value)
{
  for (int i=0; i<6; i++) {
    if (dado[n][i] == value)
      return i;
  }
  return -1;
}

int main(void) {
  
  // le entrada
  cin >> n;
  int ordem[n];

  for (int i=0;i<n;i++) {
    ordem[i] = i;
    for (int j=0;j<6;j++)
      cin >> dado[i][j];
  }
  // processa

  int resultado = 0;

  do {
    for (int primeiro = 0; primeiro <6; primeiro++) {
      int base_anterior = dado[ordem[0]][lado[primeiro]];
      int soma = max_lado(ordem[0], primeiro);
      for (int k=1; k<n; k++) {
	int i = ordem[k];
	int topo_corrente = encontra(i,base_anterior);
	soma += max_lado(i,topo_corrente);
	base_anterior = dado[i][lado[topo_corrente]];
      }
      if (soma > resultado)
	resultado = soma;
    }
  } while (next_permutation(ordem, ordem + n));
  
  // escreve resultado
  cout << resultado << endl;
  
  return 0;
}
