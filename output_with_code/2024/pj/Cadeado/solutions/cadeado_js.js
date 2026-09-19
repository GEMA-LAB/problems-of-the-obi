/*
OBI 2024 - Fase 3
  Cadeado
  Solução em O(N) com iteração e análise de casos
*/

var n;
scanf("%d", "n");

var s = Array(n);
var c = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%d %d", "s[i]", "c[i]");
}

var clicks = 0;
for (var i = 0; i < n; i++) {
  if (s[i] < c[i]) {
    var hor = c[i] - s[i];
    var anti_hor = 10 + s[i] - c[i];
    clicks += Math.min(hor, anti_hor);
  } else {
    var anti_hor = s[i] - c[i];
    var hor = 10 + c[i] - s[i];
    clicks += Math.min(hor, anti_hor);
  }
}

printf("%d\n", clicks);
