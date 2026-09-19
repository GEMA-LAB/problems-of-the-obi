
var n, m;
scanf("%d %d", "n", "m");
var bandeja = Array(n);
for (var i = 0; i < n; i++) {
  bandeja[i] = Array(m);
  for (var j = 0; j < m; j++) {
    scanf("%d", "bandeja[i][j]");
  }
}

var organizada = Array(2);
var cnt = Array(2);
organizada[0] = Array(n); cnt[0] = 0;
organizada[1] = Array(n); cnt[1] = 0;
// opcao 1: P I P I P ...
// opcao 2: I P I P I ...
for (var i = 0; i < n; i++) {
  organizada[0][i] = Array(m);
  organizada[1][i] = Array(m);
  for (var j = 0; j < m; j++) {
    var paridade = (i + j) % 2;
    if (bandeja[i][j] % 2 != paridade) {
      organizada[0][i][j] = bandeja[i][j] + 1;
      organizada[1][i][j] = bandeja[i][j];
      cnt[0]++;
    } else {
      organizada[0][i][j] = bandeja[i][j];
      organizada[1][i][j] = bandeja[i][j] + 1;
      cnt[1]++;
    }
  }
}

var opt = 0;
if (cnt[0] > cnt[1]) opt = 1;
printf("%d\n", cnt[opt]);

for (var i = 0; i < n; i++) {
  for (var j = 0; j < m; j++) {
    printf("%d", organizada[opt][i][j]);
    if (j < m - 1) printf(" ");
  }
  printf("\n");
}
