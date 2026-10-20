var n;
scanf("%d", "n");

var resp = [0, 0, 0, 0];
for (var i = 1; i <= n; i++) {
  for (var j = 1; j <= n; j++) {
    for (var k = 1; k <= n; k++) {
      var bordas = 0;
      if (i == 1 || i == n) bordas++;
      if (j == 1 || j == n) bordas++;
      if (k == 1 || k == n) bordas++;
      resp[bordas]++;
    }
  }
}

for (var i = 0; i < 4; i++) {
  printf("%d\n", resp[i]);
}
