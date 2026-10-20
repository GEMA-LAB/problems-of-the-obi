// OBI 2023 - Fase 2
// Grupos - Solução linear com vetor de marcação
// Mateus Bezrutchka
//

const MAXN = 1000100;
const MAXM = 100100;

var x, y, z;

var E, M, D;
scanf("%d", "E");
scanf("%d", "M");
scanf("%d", "D");

var juntos = Array(MAXM);
for (var i = 0; i < M; i++) {
  scanf("%d", "x");
  scanf("%d", "y");
  juntos[i] = [x, y];
}

var separados = Array(MAXM);
for (var i = 0; i < D; i++) {
  scanf("%d", "x");
  scanf("%d", "y");
  separados[i] = [x, y];
}

// vamos guardar, para cada estudante, o indice do grupo dele
var grupo = Array(MAXN);
for (var i = 0; i < E / 3; i++) {
  scanf("%d", "x");
  scanf("%d", "y");
  scanf("%d", "z");
  grupo[x] = i;
  grupo[y] = i;
  grupo[z] = i;
}

// agora checamos todas as violações
var num_violacoes = 0;

for (var i = 0; i < M; i++) {
  x = juntos[i][0];
  y = juntos[i][1];
  if (grupo[x] != grupo[y]) {
    num_violacoes++;
  }
}

for (var i = 0; i < D; i++) {
  x = separados[i][0];
  y = separados[i][1];
  if (grupo[x] == grupo[y]) {
    num_violacoes++;
  }
}

printf("%d\n", num_violacoes);
