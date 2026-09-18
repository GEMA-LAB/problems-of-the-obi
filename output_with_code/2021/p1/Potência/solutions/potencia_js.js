// OBI2021 - Fase 2
// Potência


var n, t;
var resposta = 0;
var potencia, p, base;
  
scanf("%d", "n");

for (var i=0; i<n; i++) {
    scanf("%d", "t");
    p = t % 10;
    base = Math.floor(t / 10);
    
    potencia = 1;
    for (var j=0; j<p; j++)
	potencia *= base;
    
    resposta += potencia;
}

printf("%d\n", resposta);
