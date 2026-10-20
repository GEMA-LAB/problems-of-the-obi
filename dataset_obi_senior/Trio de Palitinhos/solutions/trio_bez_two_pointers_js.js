
var n;
scanf("%d", "n");

var v = new Array(n);
for (var i = 0; i < n; i++) {
    scanf("%d", "v[i]");
}

v.sort((x, y) => x - y);

var resp = 0;

for (var i = 0; i < n; i++) {
    var l = 0;
    for (var r = i - 1; r >= 1; r--) {
        while (l < r && v[l] + v[r] <= v[i]) {
            l++;
        }
        if (l < r) {
            resp += (r - l);
        }
    }
}

printf("%d\n", resp);
