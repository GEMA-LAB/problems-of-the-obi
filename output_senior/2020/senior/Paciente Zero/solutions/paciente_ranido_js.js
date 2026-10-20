////
// Paciente Zero - OBI2020
////

var n, c;
var i, j, k, x;

scanf("%d%d","n","c");

var infectados = new Set();
for (i=1; i<=n; i++)
  infectados.add(i);

for (i=1; i<=c; i++) {
    scanf("%d","x");
    scanf("%d","k");
    for (j=0; j<k; j++) {
        scanf("%d","x");
	infectados.delete(x);
    }
}

infectados = Array.from(infectados);

for (i=0; i<infectados.length; i++)
   printf("%d\n",infectados[i]);
