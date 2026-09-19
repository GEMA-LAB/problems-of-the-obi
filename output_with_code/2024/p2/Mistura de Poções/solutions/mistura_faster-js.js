var n, k;
scanf("%d%d", "n", "k");

var a = Array(n);
var chk = 32;
var sz = ~~(n / chk);
var x = Array(chk);
for (var i = 0; i < sz; ++i) {
    scanf(
        "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
        "x[0]", "x[1]", "x[2]", "x[3]", "x[4]", "x[5]", "x[6]", "x[7]", "x[8]", "x[9]",
        "x[10]", "x[11]", "x[12]", "x[13]", "x[14]", "x[15]", "x[16]", "x[17]", "x[18]", "x[19]",
        "x[20]", "x[21]", "x[22]", "x[23]", "x[24]", "x[25]", "x[26]", "x[27]", "x[28]", "x[29]",
        "x[30]", "x[31]"
    );
    for (var j = 0; j < chk; ++j) a[i * chk + j] = x[j];
}
sz = n % chk;
for (var i = 0; i < sz; ++i) {
    var y;
    scanf("%d", "y");
    a[n - sz + i] = y;
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
