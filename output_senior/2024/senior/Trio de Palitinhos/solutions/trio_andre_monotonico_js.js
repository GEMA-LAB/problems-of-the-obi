var n;
scanf("%d", "n");

var a = new Array(n);
for (var i = 0; i < n; i++) {
    scanf("%d", "a[i]");
}

a.sort((x, y) => x - y);

var resp = 0, i;

for (var i = 0; i <= n - 3; i++) {
    var k = i + 2;
    for (var j = i + 1; j <= n - 2; j++) {
        k = Math.max(k, j + 1);
        while (k < n && (a[i] + a[j] > a[k])) {
            k++;
        }
        resp += (k - 1) - j;
    }
}

printf("%d\n", resp);
