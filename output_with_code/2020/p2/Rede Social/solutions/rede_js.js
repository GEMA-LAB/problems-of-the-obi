// OBI2020 - Fase 3                                                                        // rede social


var n;
var repostagens = [];

scanf("%d", "n");

for (var i=0; i<n; i++) {
    scanf("%d", "repostagens[i]");
}

// ordena do maior para o menor
repostagens.sort((a,b)=>b-a);

// calcula o fator de influencia
var fi = 0;
while (fi < n && repostagens[fi] >= fi + 1)
    fi++;

// imprime o resultado
printf("%d\n", fi);
