var n, t;
scanf("%d %d", "n", "t");
var tipo = Array(n);
var preco = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%d", "tipo[i]");
}
for (var i = 0; i < n; i++) {
  scanf("%d", "preco[i]");
}
var c;
var cliente = Array(c);
scanf("%d", "c");
for (var i = 0; i < c; i++) {
  scanf("%d", "cliente[i]");
}

// [preco, tipo, indice]
todos_objetos = Array(n);
precos_para_tipo = Array(t + 1);
for (var i = 1; i <= t; i++) {
  precos_para_tipo[i] = Array();
}
for (var i = 0; i < n; i++) {
  todos_objetos[i] = [preco[i], tipo[i], i];
  precos_para_tipo[tipo[i]].push([preco[i], tipo[i], i]);
}

usado = new Array(n).fill(false);
// pos[0] -- ponteiro dos indecisos em todos_objetos
// pos[t] -- ponteiro dos decididos em precos_para_tipo[t]
pos = new Array(t + 1).fill(0);

function cmp(a, b) {
  if (a[0] != b[0]) return a[0] - b[0];
  if (a[1] != b[1]) return a[1] - b[1];
  return a[2] - b[2];
}

for (var i = 1; i <= t; i++) {
  precos_para_tipo[i].sort(cmp);
}
todos_objetos.sort(cmp);

var resp = 0;
for (var i = 0; i < c; i++) {
  var u = cliente[i];
  var cur_obj = [-1, -1, -1];
  if (u == 0) {
    while (pos[0] < n) {
      cur_obj = todos_objetos[pos[0]];
      if (!usado[cur_obj[2]]) break;
      pos[0]++;
    }
  } else {
    while (pos[u] < precos_para_tipo[u].length) {
      cur_obj = precos_para_tipo[u][pos[u]];
      if (!usado[cur_obj[2]]) break;
      pos[u]++;
    }
  }
  if (cur_obj[2] == -1 || usado[cur_obj[2]]) continue;
  usado[cur_obj[2]] = true;
  resp += cur_obj[0];
}

printf("%d\n", resp);

