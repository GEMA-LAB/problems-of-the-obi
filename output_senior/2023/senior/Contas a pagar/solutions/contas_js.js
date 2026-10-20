// OBI2023
// Tarefa Contas a pagar
// r. anido


function compara(a, b) {
    return a - b;
}

var valor;
var acougue;
var farmacia;
var padaria;

scanf("%d", "valor");
scanf("%d", "acougue");
scanf("%d", "farmacia");
scanf("%d", "padaria");

var resp = 0;

var contas = [acougue, farmacia, padaria];
contas.sort(compara);

if (contas[0] + contas[1] + contas[2] <= valor)
    resp = 3;
else if (contas[0] + contas[1] <= valor)
    resp = 2;
else if (contas[0] <= valor)
    resp = 1;
else
    resp = 0;

printf("%d\n", resp);
