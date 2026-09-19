// OBI2023
// Tarefa Prefixo
// r. anido

var n, m;
var palavra1, palavra2;

scanf("%d", "n");
scanf("%s", "palavra1");

scanf("%d", "m");
scanf("%s", "palavra2");


var resp = 0;
var i = 0;
while (i < n && i < m) {
    if (palavra1[i] == palavra2[i])
	resp++;
    else
	break;
    i++;
}


printf("%s\n", resp);
