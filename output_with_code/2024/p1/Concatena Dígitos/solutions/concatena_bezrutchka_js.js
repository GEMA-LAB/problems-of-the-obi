var n;
var q;
scanf("%d %d", "n", "q");

var v = Array(n + 1);
var psum = Array(n + 1);
psum[0] = 0;
for (var i = 1; i <= n; i++) {
  scanf("%d", "v[i]");
  psum[i] = psum[i - 1] + v[i];
}

while (q > 0) {
  var l, r;
  scanf("%d %d", "l", "r");
  var tam = r - l + 1;
  var soma = psum[r] - psum[l - 1];
  var resp = (tam - 1) * soma * 11;
  printf("%d\n", resp);
  q--;
}
