// OBI2023
// Tarefa Pizza
// r. anido

var n, g, m;

scanf("%d", "n");
scanf("%d", "g");
scanf("%d", "m");

var sobra =  g*8 + m*6 - n;

if (sobra < 0)
    sobra = 0;

printf("%d\n", sobra);
