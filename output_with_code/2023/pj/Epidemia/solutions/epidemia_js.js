// OBI2023
// Tarefa Epidemia
// r. anido

var n, r, p;

scanf("%d%d%d", "n", "r", "p");

var total = n;
var dias = 0;

while (total < p) {
    n *= r;
    total += n;
    dias += 1;
}

printf("%d\n", dias);
