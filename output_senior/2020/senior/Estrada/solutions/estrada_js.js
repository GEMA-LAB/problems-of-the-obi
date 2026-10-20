// OBI2020 - Fase 2                                                                                                                            
// estrada                                                                                                                                     


var t, n;
var compr_oeste = 0;
var compr_leste = 0;
var dif_oeste, dif_leste;
var compr, compr_min;

scanf("%d%d", "t", "n");
var cidades=[];

for (var i=0; i<n; i++) {
    scanf("%d", "cidades[i]");
}

cidades.sort((a,b)=>a-b);

// inicia com a extensao do primeiro trecho a oeste                                                                                            
compr_min = cidades[0] + (cidades[1] - cidades[0])/2.0;
for (var i=1; i<n-1; i++) {
    dif_oeste = cidades[i] - cidades[i-1];
    dif_leste = cidades[i+1] - cidades[i];
    compr = dif_oeste/2.0 + dif_leste/2.0;
    if (compr < compr_min)
        compr_min = compr;
}

// extensao do ultimo trecho a leste                                                                                                           
compr = (cidades[n-1] - cidades[n-2])/2.0 + (t - cidades[n-1]);
if (compr < compr_min)
    compr_min = compr;

printf("%.2f\n", compr_min);
