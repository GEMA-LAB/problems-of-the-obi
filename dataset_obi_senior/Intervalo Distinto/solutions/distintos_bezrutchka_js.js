// OBI 2023 - Fase 2
// Distintos - Solução O(N) gulosa usando dois ponteiros
// Mateus Bezrutchka
//

const MAXN = 100100;

var n;
scanf("%d", "n");

var v = Array(MAXN);
for (var i = 1; i <= n; i++) {
  var x;
  scanf("%d", "x");
  v[i] = x;
}

// inicializando vetor de marcação
var ultimo_id = Array(MAXN);
for (var i = 0; i < MAXN; i++) {
  ultimo_id[i] = 0;
}

var resp = 0;
var inicio = 1;
// para o fim atual, inicio guarda o menor índice
// tal que [inicio, fim] nao tem repetições
for (var fim = 1; fim <= n; fim++) {
  var x = v[fim];
  if (ultimo_id[x] >= inicio) {
    inicio = ultimo_id[x] + 1;
  }
  resp = Math.max(resp, fim - inicio + 1);
  ultimo_id[x] = fim;
}

printf("%d\n", resp);
