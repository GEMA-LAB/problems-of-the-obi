// OBI2022
// Tarefa Caminho
// r. anido

var postes = [];

var n;

scanf("%d", "n");
for (var i=1; i<=n; i++)
    scanf("%d", "postes[i]");

// vamos copiar os postes para levar em conta a circularidade
for (var i=n+1; i<=2*n; i++)
    postes[i] = postes[i-n];
  
var max_compr = 0;
var cur_compr = 0;
for(var i=1; i<2*n; i++) {
    if(postes[i] + postes[i+1] < 1000)
	cur_compr++;
    else
	cur_compr = 0;
    if (cur_compr > max_compr)
	max_compr = cur_compr;

}

if (max_compr > n)
    max_compr = n

printf("%d\n", max_compr);

