var n;
scanf("%d", "n");

var resp = 0;
while (n > 0) {
  var x = n;
  var maxDigit = 0;
  while (x > 0) {
    var digit = x % 10;
    maxDigit = Math.max(maxDigit, digit);
    x = Math.floor(x / 10);
  }
  n -= maxDigit;
  resp++;
}

printf("%d\n", resp);
