/**
 * OBI 2023 - Fase 3
 * Tesouro da Quadradônia - Solução O(N^2) usando matriz auxiliar
 *                          para marcar posições visitadas
 * Mateus Bezrutchka
 **/

var n;
scanf("%d", "n");

var mapa = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%s", "mapa[i]");
}

var A, B;
scanf("%d", "A");
scanf("%d", "B");
// estou indexando do 0
A--;
B--;

// marca areas que eu ja visitei antes para identificar loop infinito
var visitado = Array(n);
for (var i = 0; i < n; i++) {
  visitado[i] = Array(n).fill(false);
}

// (x, y) mantém a posição atual
var x = A;
var y = B;
var minutos = 0;

while (true) {
  if (x < 0 || x >= n || y < 0 || y >= n) {
    // caiu na água
    printf("-1\n");
    return;
  }
  if (visitado[x][y] == true) {
    // entrou em loop
    printf("0\n");
    return;
  }
  if (mapa[x][y] == 'X') {
    // encontrou o tesouro
    printf("%d\n", minutos);
    return;
  }
  // move pra próxima área
  visitado[x][y] = true;
  minutos++;
  if (mapa[x][y] == 'N') x--;
  else if (mapa[x][y] == 'S') x++;
  else if (mapa[x][y] == 'O') y--;
  else y++;
}
