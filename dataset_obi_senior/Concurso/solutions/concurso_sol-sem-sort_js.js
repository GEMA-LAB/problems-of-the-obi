var n, k;
scanf("%d %d", "n", "k");
var v = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%d", "v[i]");
}

for (var nota = 100; nota >= 1; nota--) {
  var cont = 0;
  for (var i = 0; i < n; i++) {
    if (v[i] >= nota) {
      cont++;
    }
  }
  if (cont >= k) {
    printf("%d\n", nota);
    break;
  }
}
