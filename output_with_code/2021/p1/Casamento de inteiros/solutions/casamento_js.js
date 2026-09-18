// OBI2021 - Fase 3
//Casamento

var a, b;

scanf("%s","a");
scanf("%s","b");

// ajusta os tamanhos adicionando zeros à esquerda
while (a.length < b.length)
    a = "0" + a;
while (b.length < a.length)
    b = "0" + b;

var na = "";
var nb = "";

for (var i=0; i<a.length; i++){
    if (a[i] == b[i]) {
        na += a[i];
        nb += b[i];
    }
    else if (a[i] < b[i])
      nb += b[i];
  else
      na += a[i];
}

if (na.length == 0)
    res1 = -1;
else
    res1 = parseInt(na,10);

if (nb.length == 0)
    res2 = -1;
else
    res2 = parseInt(nb,10);

if (res2 > res1)
    printf("%d %d\n",res1,res2);
else
    printf("%d %d\n",res2,res1);
    

    
