// OBI2021 - Fase 2
// Cálculo rápido

var s, a, b;
var resposta = 0;

scanf("%d", "s");
scanf("%d", "a");
scanf("%d", "b");

// para cada número no intervalo, soma os dígitos
// e compara com s
for (var i=a; i<=b; i++) {
    var soma = 0, num = i;
    while (num > 0) {
	soma += num % 10;
        num = Math.floor(num / 10);
    }
    if (soma == s)
	resposta++;
}
printf("%d\n", resposta);

