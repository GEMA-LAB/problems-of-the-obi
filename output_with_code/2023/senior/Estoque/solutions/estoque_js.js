// OBI2023
// Tarefa Chinelos
// r. anido

var n, m;
var x;

scanf ("%d %d", "m", "n");

var estoque = [];

for (var i = 0; i < m; i++) {
    estoque.push(new Array(n).fill(0));
}

for (var i=0; i<m; i++) {
   for (var j=0; j<n; j++) {
      scanf ("%d", "x");
      estoque[i][j] = x;
   }
}

var total = 0;
var p;

scanf("%d", "p");

for (var i=0; i<p; i++) {
   var tipo, tamanho;
   scanf("%d %d", "tipo", "tamanho");
   if (estoque[tipo-1][tamanho-1] > 0) {
      estoque[tipo-1][tamanho-1] -= 1;
      total += 1;
   }
}

printf("%d\n", total);
