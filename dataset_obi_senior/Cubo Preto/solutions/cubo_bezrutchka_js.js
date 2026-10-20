var n;
scanf("%d", "n");

var resp = Array(4);
if (n == 2) {
  resp[0] = resp[1] = resp[2] = 0;
} else {
  resp[0] = (n - 2) * (n - 2) * (n - 2);
  resp[1] = 6 * (n - 2) * (n - 2);
  resp[2] = 12 * (n - 2);
}
resp[3] = 8;

for (var i = 0; i < 4; i++) {
  printf("%d\n", resp[i]);
}
