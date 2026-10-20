var MAXN = 101;
var MAXT = 101;
var comprei = new Array(MAXT).fill(false);  // Se já comprei fruta desse tipo
var tipo = new Array(MAXN).fill(0);
var preco = new Array(MAXN).fill(0);

var dinheiro, numFrutas;
scanf("%d %d", "dinheiro", "numFrutas");

for (var i = 0; i < numFrutas; i++) {
  scanf("%d %d", "tipo[i]", "preco[i]");
}

var resp = 0;

while (true) {
  // Procuro a melhor fruta pra comprar
  var maisBarata = -1;
  for (var i = 0; i < numFrutas; i++) {
    if (comprei[tipo[i]]) {
      // Comprar tipo repetido é inútil
      continue;
    }
    if (maisBarata === -1 || preco[i] < preco[maisBarata]) {
      maisBarata = i;
    }
  }

  // Vejo se já acabou o dinheiro
  if (maisBarata === -1 || preco[maisBarata] > dinheiro) {
    break;
  }

  // Compro a fruta
  resp++;
  dinheiro -= preco[maisBarata];
  comprei[tipo[maisBarata]] = true;
}

printf("%d\n", resp);
