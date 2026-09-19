var n;
scanf("%d", "n");
var tipo = Array(n);
var preco = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%d", "tipo[i]");
}
for (var i = 0; i < n; i++) {
  scanf("%d", "preco[i]");
}
var c;
scanf("%d", "c");
var cliente = Array(c);
for (var i = 0; i < c; i++) {
  scanf("%d", "cliente[i]");
}

var precos = Array(3);
precos[1] = Array(); precos[2] = Array();
for (var i = 0; i < n; i++) {
  if (tipo[i] == 1) precos[1].push(preco[i]);
  else precos[2].push(preco[i]);
}

precos[1].sort((a, b) => a - b);
precos[2].sort((a, b) => a - b);
var pos = Array(3);
pos[1] = 0; pos[2] = 0;
var len_1 = precos[1].length, len_2 = precos[2].length;

var resp = 0;
for (var i = 0; i < c; i++) {
  var tipo = -1;
  if (cliente[i] == 1) {
    if (pos[1] < len_1) tipo = 1;
  } else if (cliente[i] == 2) {
    if (pos[2] < len_2) tipo = 2;
  } else {
    if (pos[1] == len_1 && pos[2] == len_2) tipo = -1;
    else if (pos[1] == len_1) tipo = 2;
    else if (pos[2] == len_2) tipo = 1;
    else if (precos[1][pos[1]] <= precos[2][pos[2]]) tipo = 1;
    else tipo = 2;
  }

  if (tipo == -1 || (tipo == 1 && pos[1] == len_1) || (tipo == 2 && pos[2] == len_2)) {
    continue;
  }
  resp += precos[tipo][pos[tipo]];
  pos[tipo]++;
}

printf("%d\n", resp);
