/*
  OBI 2025 - Fase 1
  Cafeteria
*/

var a, b, c, d;
scanf("%d", "a");
scanf("%d", "b");
scanf("%d", "c");
scanf("%d", "d");

var possivel = false;

// testa todas as quantidades de doses
for (var doses = 1; doses * d <= c; doses++) {
  var leite = c - doses * d;
  if (a <= leite && leite <= b) {
    possivel = true;
  }
}

if (possivel) {
  printf("S\n");
} else {
  printf("N\n");
}
