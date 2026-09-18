var d;
scanf("%d", "d");

// Math.floor arredonda pra baixo
var ponto_antes = Math.floor(d / 400) * 400;
var dist_antes = d - ponto_antes;

var ponto_depois = ponto_antes + 400;
var dist_depois = ponto_depois - d;

printf("%d\n", Math.min(dist_antes, dist_depois))
