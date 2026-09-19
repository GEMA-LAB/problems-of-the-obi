var preco=[];
var sol = 0;
var tmp;

// le a entrada
scanf("%d", "n");
for (var i=0; i<n; i++) {
   scanf("%d", "preco[i]");
}

// ordena do maior para o menor preco
preco.sort((a,b)=>a-b).reverse();

// não paga a cada três chocolates
for (var i=0; i<n; i++) {
   if (i % 3 == 2) {
      continue;
   }
   sol += preco[i];
}
printf("%d\n", sol);
