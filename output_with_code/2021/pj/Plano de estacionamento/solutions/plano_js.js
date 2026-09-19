
var x, n, k;
var soma = 0;

scanf("%d","x");
scanf("%d","n");

for (var i=0; i<n; i++) {
    scanf("%d","k");
    soma += k;
}

printf("%d\n", x*(n+1) - soma);
