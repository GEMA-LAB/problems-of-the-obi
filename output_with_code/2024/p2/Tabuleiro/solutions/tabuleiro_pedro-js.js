const M = 1000 * 1000 * 1000 + 7;

var n;
scanf("%d", "n");

var a = 0, b = 0, c = 1;
for (var i = 0; i < n; ++i) {
    var x = c + 2 * (a + b);
    x %= M;
    a = b;
    b = c;
    c = x;
}

printf("%d\n", c);
