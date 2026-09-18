/*
OBI 2024 - Fase 3
  Amigos
  Solução em O(N)

  A observação principal neste problema é de nunca é
  ótimo um integrante do grupo fazer uma troca com um
  outro integrante do grupo (pois essa troca não mudaria
  em nada as posições dos integrantes). Portanto, os
  integrantes em cada lado da mesa se mantêm sempre na
  mesma ordem (entre eles) que estavam no início.

  Assim, o seguinte algoritmo guloso funciona:
  Pareie os integrantes em cada lado da esquerda para
  a direita, ou seja: o primeiro integrante do lado
  superior com o primeiro do lado inferior, o segundo
  do lado superior com o segundo do lado inferior, e
  assim em diante. Basta então somar as distâncias
  de cada par.

  Uma prova formal de que o algoritmo guloso está
  correto pode ser feita com argumento de troca.
*/

#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k; scanf("%d %d", &n, &k);
  vector<int> posicoesAmigosSuperior, posicoesAmigosInferior;
  for(int i = 0; i < n; i++) {
    int amigo; scanf("%d", &amigo);
    if(amigo == 1) posicoesAmigosSuperior.push_back(i);
  }
  for(int i = 0; i < n; i++) {
    int amigo; scanf("%d", &amigo);
    if(amigo == 1) posicoesAmigosInferior.push_back(i);
  }
  long long int trocas = 0;
  for(int i = 0; i < k; i++)
    trocas += abs(posicoesAmigosSuperior[i] - posicoesAmigosInferior[i]);
  printf("%lld\n", trocas);
}