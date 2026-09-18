
var n;
scanf("%d", "n");

var a = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%d", "a[i]");
}

a.sort((a, b) => a - b);

var resp = 0, cnt = 1;

for (var i = 1; i < n; i++) {
  if (a[i] == a[i - 1]) cnt++;
  else {
    resp += Math.floor(cnt / 2);
    cnt = 1;
  }
}
resp += Math.floor(cnt / 2);

printf("%d\n", resp);
