// OBI2022
// Fase 3
// Restaurante de pizza

var a;
var b;
var raio;
var grau;

    
scanf("%d","a");
scanf("%d","b");
scanf("%d","raio");
scanf("%d","grau");

var ok = true;

if (2*raio > a || 2*raio > b)
    ok = false;

if ((360 % grau) != 0)
    ok = false;

if (ok)
    printf("S\n");
else
    printf("N\n");
