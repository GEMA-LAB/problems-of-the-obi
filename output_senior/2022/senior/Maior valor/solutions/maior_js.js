// OBI2022
// Tarefa Maior

var N, M, S;

scanf("%d%d%d","N","M","S");

var achou = false;
var resp;
		
for (var i=M; i>N; i--) {
    var soma = 0;
    var x = i;
    while (x > 0) {
	soma += x % 10;
	x /= 10;
	x = Math.floor(x)
    }
    if (soma == S) {
	achou = true;
	resp = i;
	break;
    }
}	    

if (achou)
    printf("%d\n",resp);
else
    printf("-1\n");
