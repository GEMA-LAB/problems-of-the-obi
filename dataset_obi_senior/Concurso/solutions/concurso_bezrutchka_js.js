var n;
var k;
scanf("%d %d", "n", "k");

var v = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%d", "v[i]");
}

// pass comparison function to sort in increasing order
v.sort((x, y) => x - y);

printf("%d\n", v[n - k]);
