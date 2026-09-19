// OBI2022
// Tarefa teste de redacao

var n, m;

var letras = Array.from("abcdefghijklmnopqrstuvwxyz");

scanf ("%d%d", "n", "m");
  
for (var i=1; i<=m; i++) {
    var x = i;
    while (x > 0) {
	printf("%s", letras[x % 10]);
	x = x / 10;
	x = Math.floor(x)
	printf(" ");
    }
}

printf("\n");

