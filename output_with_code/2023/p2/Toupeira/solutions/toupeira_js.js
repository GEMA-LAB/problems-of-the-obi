// OBI2023
// Tarefa Toupeira
// r. anido


var s, t;

scanf("%d %d", "s", "t");

var adj = [];

for (var i = 0; i < s; i++) {
    adj.push(new Array(s).fill(false));
}

for (var i=0; i<t; i++) {
    var x, y;
    scanf("%d %d", "x", "y");
    x -= 1;
    y -= 1;
    adj[x][y] = true;
    adj[y][x] = true;
}

var p;
scanf("%d", "p");

var total = 0;
for (var i=0; i<p; i++) {
    var n, corrente;
    scanf("%d %d", "n", "corrente");
    corrente -= 1;
    var ok = true;
    for (var j=0; j<n-1; j++) {
	var k;
	scanf("%d", "k");
	k -= 1;
	if (adj[corrente][k])
	    corrente = k;
	else {
	    ok = false;
	}
    }
    if (ok)
	total += 1;
}
printf("%d\n", total);

