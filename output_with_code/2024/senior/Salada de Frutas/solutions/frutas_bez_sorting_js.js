var dinheiro, numFrutas;
scanf("%d %d", "dinheiro", "numFrutas");

var frutas = [];
for (var i = 0; i < numFrutas; i++) {
  var tipo, preco;
  scanf("%d %d", "tipo", "preco");
  frutas.push([preco, tipo]);
}

// Ordena por preço
frutas.sort(function(a, b) {
  return a[0] - b[0];
});

// Se já comprei fruta desse tipo
var comprei = new Array(101).fill(false);
var resp = 0;

for (var j = 0; j < frutas.length; j++) {
  var fruta = frutas[j];
  var preco = fruta[0];
  var tipo = fruta[1];
  if (comprei[tipo]) {
    // Comprar tipo repetido é inútil
    continue;
  }
  if (preco > dinheiro) {
    // Todos daqui pra frente vão ser mais caros do que meu dinheiro
    break;
  }
  // Compro a fruta
  resp++;
  dinheiro -= preco;
  comprei[tipo] = true;
}

printf("%d\n", resp);
