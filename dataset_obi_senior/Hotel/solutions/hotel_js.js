// OBI2022
// Tarefa hotel

var d, a, n;

scanf("%d%d%d","d","a","n");

//vamos usar chegada para calcular o valor da diária
var chegada = n;

if (chegada > 15)
    chegada = 15;

var diaria = d + (chegada-1)*a;

printf("%d\n",(31 - n + 1)*diaria);
