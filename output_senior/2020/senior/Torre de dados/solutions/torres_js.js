// torre de dados
// obi2020 - fase 3

var n, i, j;
var lado = [5, 3, 4, 1, 2, 0];

function max_lado(n, top) {
   var bottom = lado[top];
   var max=0;
   for (var i=0; i<6; i++) {
      if (i==top || i==bottom) continue;
      if (max < dado[n][i])
         max = dado[n][i];
   }
   return max;
}

function encontra(n, value) {
   for (var i=0; i<6; i++) {
      if (dado[n][i] == value)
         return i;
   }
   return -1;
}

// le entrada
scanf("%d","n");

var dado = [n];
for (j=0;j<n;j++)
   dado[j] = [];


for (i=0;i<n;i++)
   for (j=0;j<6;j++)
      scanf("%d","dado[i][j]");
  
// processa
var resultado = 0;
for (var primeiro = 0; primeiro < 6; primeiro++) {
   var base_anterior = dado[0][lado[primeiro]];
   var soma = max_lado(0, primeiro);
   for (var i=1;i<n;i++) {
      var topo_corrente = encontra(i,base_anterior);
      soma += max_lado(i,topo_corrente);
      base_anterior = dado[i][lado[topo_corrente]];
   }
   if (soma > resultado)
      resultado = soma;
}


// escreve resultado
printf("%d\n", resultado);
