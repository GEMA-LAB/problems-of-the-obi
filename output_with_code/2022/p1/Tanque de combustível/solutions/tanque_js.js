// OBI2022
// Tarefa tanque

var c, d, t;

scanf ("%d%d%d", "c", "d", "t");

var litros = d / c;

var compra = litros - t;

if (compra < 0)
    compra = 0;

printf("%.1f\n", compra);

