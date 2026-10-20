// OBI2022
// Tarefa Chuva


var MAX = 1000000;
var somas= [];
var n, s, v;

scanf("%d%d","n","s");
var soma = 0;
var resp = 0;

// popula vetor somas com zeros
for (var i=0; i<MAX; i++)
    somas.push(0);

somas[0] = 1;
for (var i=0; i<n; i++) {
    scanf("%d", "v");
    soma += v;
    if (soma - s >= 0)
	resp += somas[soma - s];
    somas[soma]++;
}

printf("%d\n", resp);
