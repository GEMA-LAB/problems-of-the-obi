var n, k;
scanf("%d", "n");
scanf("%d", "k");

var a = Array(n);
for (var i = 0; i < n; ++i) {
    var x;
    scanf("%d", "x");
    a[i] = x;
}

var f = Array(n + 1);
for (var i = 0; i < n + 1; ++i) f[i] = 0;

var ans = 0;

var p = 0, d = 0;
for (var i = 0; i < n; ++i) {
    if (f[a[i]] == 0) ++d;
    ++f[a[i]];
    while (d >= k) {
        --f[a[p]];
        if (f[a[p]] == 0) --d;
        ++p;
    }
    ans += p;
}

printf("%d\n", ans);
