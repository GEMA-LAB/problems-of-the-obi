var l, c, t;
scanf("%d %d %d", "l", "c", "t");

var original = new Array(l);
var linha = new Array(l);
var coluna = new Array(c);

for (var i = 0; i < l; i++) {
  original[i] = new Array(c);
  for (var j = 0; j < c; j++) {
    original[i][j] = c * i + j;
  }
  linha[i] = i;
}
for (var j = 0; j < c; j++) {
  coluna[j] = j;
}

while (t--) {
  var op, a, b;
  scanf("%s %d %d", "op", "a", "b");
  a--; b--;
  if (op == 'L') {
    var aux = linha[a];
    linha[a] = linha[b];
    linha[b] = aux;
  } else {
    var aux = coluna[a];
    coluna[a] = coluna[b];
    coluna[b] = aux;
  }
}

var resposta = new Array(l);
for (var i = 0; i < l; i++) {
  resposta[i] = new Array(j);
  for (var j = 0; j < c; j++) {
    resposta[i][j] = original[linha[i]][coluna[j]] + 1;
  }
}

for (var i = 0; i < l; i++) {
  for (var j = 0; j < c; j++) {
    printf("%d", resposta[i][j]);
    if (j == c - 1) printf("\n");
    else printf(" ");
  }
}
