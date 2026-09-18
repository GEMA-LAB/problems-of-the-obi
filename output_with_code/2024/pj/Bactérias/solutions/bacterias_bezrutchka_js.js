var n, p;
scanf("%d", "n");
scanf("%d", "p");

var pot = 1, r = 0;
while (true) {
  if (pot * p > n) break;
  pot *= p;
  r++;
}

printf("%d\n", r);
