// OBI2023
// Tarefa Código


var n;
var s;

scanf("%d", "n");
scanf("%s", "s");

var qtd = 0;
var last = '0';

for (var i = 0; i < n; i++) {
    if(s[i] == last)
	qtd++;
    else {
	if (last != '0')
	    printf(" %d %s", qtd, last);
	qtd = 1;
    }
    
    last = s[i];
  }

printf(" %d %s\n", qtd, last);
