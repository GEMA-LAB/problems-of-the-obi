// OBI2022
// fase 3 - caravana
// r. anido

var n;
var pesos = [];
var soma = 0;
var p;

scanf("%d", "n");
for (var i=0; i<n; i++) {
    scanf("%d", "p");
    soma += p;
    pesos.push(p);
  }

var ideal = soma / n;
for (var i=0; i<n; i++) {
    printf("%d\n", ideal - pesos[i]);
}
