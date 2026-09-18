// OBI2023
// Tarefa Chinelos
// r. anido

var n;

scanf ("%d", "n");

var estoque = [];
for (var i=0; i<n; i++) {
   var x;
   scanf("%d", "x");
   estoque.push(x);
}


var total = 0;
var p;

scanf("%d", "p");

for (var i=0; i<p; i++) {
   var pedido;
   scanf("%d", "pedido");
   if (estoque[pedido-1] > 0) {
      estoque[pedido-1] -= 1;
      total += 1;
   }
}

printf("%d\n", total);
