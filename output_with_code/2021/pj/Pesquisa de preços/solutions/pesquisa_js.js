// OBI2021 - Fase 2
// Pesquisa de preços


var n;
var estado;
var alcool, gasolina;
var existe = false;

scanf("%d", "n");

for (var i=0; i<n; i++) {
    scanf("%s%f%f", "estado", "alcool", "gasolina");
    if (alcool/gasolina <= 0.70) {
	printf("%s\n", estado);
	existe = true;
    }
}

// se não imprimiu nenhum estado, imprime asterisco
if (!existe)
    printf("*\n");
