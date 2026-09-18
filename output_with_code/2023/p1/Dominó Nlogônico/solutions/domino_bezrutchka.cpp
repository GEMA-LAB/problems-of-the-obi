/**
 * OBI 2023 - Fase 3
 * Dominó Nlogônico - Solução O(N) usando pilha
 * Mateus Bezrutchka
 *
 * Vamos calcular as respostas da direita para a esquerda.
 * Seja resp[i] a resposta para o dominó i.
 *
 * A todo momento, dizemos que um dominó é "líder" se ainda
 * não existe nenhum dominó à esquerda dele, já processado,
 * que derruba ele. Ao processarmos um dominó que derruba
 * alguns líderes, esse dominó vira líder de todos eles.
 *
 * Observe que
 *    resp[i] = soma(resp[k] para k líder e i derruba k)
 * pois as respostas dos líderes contém todos os dominós
 * que seriam derrubados indiretamente pelo dominó i.
 *
 * Podemos usar uma estrutura de pilha para manter os
 * líderes atuais, e assim calcular todas as respostas em
 * um tempo total de O(N).
 *
 **/
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;

const int MAXN = (int)3e5 + 10;
int x[MAXN], h[MAXN];
stack <int> pilha;
int resp[MAXN];
int n;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &x[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &h[i]);
  }

  for (int i = n; i >= 1; i--) {
    resp[i] = 1;

    while (!pilha.empty()) {
      int cur_top = pilha.top();
      if (x[i] + h[i] < x[cur_top]) break;
      resp[i] += resp[cur_top];
      pilha.pop();
    }

    pilha.push(i);
  }

  for (int i = 1; i <= n; i++) {
    printf("%d%c", resp[i], i == n ? '\n' : ' ');
  }
  return 0;
}
