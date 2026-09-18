// OBI-2020
// Tarefa Piloto Automático
// r. anido

var A, B, C;

scanf("%d","A");
scanf("%d","B");
scanf("%d","C");

var distanciaAB = B - A;
var distanciaBC = C - B;

if (distanciaAB < distanciaBC)
    printf("1");
else if (distanciaAB > distanciaBC)
    printf("-1");
else 
    printf("0");
