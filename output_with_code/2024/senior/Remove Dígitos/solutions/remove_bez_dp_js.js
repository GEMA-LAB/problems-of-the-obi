var n;
scanf("%d", "n");

var dp = new Array(n + 1).fill(1e9);
dp[0] = 0;
for (var i = 1; i <= n; i++) {
  var x = i;
  while (x > 0) {
    var digit = x % 10;
    if (digit > 0) {
      dp[i] = Math.min(dp[i], dp[i - digit] + 1);
    }
    x = Math.floor(x / 10);
  }
}

printf("%d\n", dp[n]);
