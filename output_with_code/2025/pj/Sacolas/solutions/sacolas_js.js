var n, s;
scanf("%d %d", "n", "s");

var sum = 0, res = 1;
for (var i = 0; i < n; i++) {
  var x;
  scanf("%d", "x");
  if (sum + x > s) {
    sum = x;
    res++;
  } else {
    sum += x;
  }
}

printf("%d\n", res);
