
var freq = Array(100001).fill(0);

var n;
scanf("%d", "n");

for (var i = 0; i < n; i++) {
  var alt;
  scanf("%d", "alt");
  freq[alt]++;
}

var resp = 0;
for (var i = 1; i <= 100000; i++) {
  resp += Math.floor(freq[i] / 2);
}

printf("%d\n", resp);
