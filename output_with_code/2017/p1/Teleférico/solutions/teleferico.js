var C,A;
var quociente, resto, resposta;

scanf("%d%d", "C", "A");

quociente = A/(C-1);
resto = A%(C-1);
resposta = quociente;
if (resto > 0) 
    resposta=resposta+1;

printf("%d\n",resposta);
