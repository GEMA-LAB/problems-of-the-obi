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

var n;
scanf("%d", "n");

var x = Array(n);
var h = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%d ", "x[i]");
}
for (var i = 0; i < n; i++) {
  scanf("%d ", "h[i]");
}

var stack = Array(n);
var ans = Array(n);
var cur_len = 0;

for (var i = n - 1; i >= 0; i--) {
  ans[i] = 1;
  while (cur_len > 0) {
    var cur_top = stack[cur_len - 1];
    if (x[i] + h[i] < x[cur_top]) {
      break;
    }
    ans[i] += ans[cur_top];
    cur_len--;
  }
  stack[cur_len] = i;
  cur_len++;
}

for (var i = 0; i < n - 1; i++) {
  printf("%d ", ans[i]);
}
printf("%d\n", ans[i]);
