var n;
scanf("%d", "n");
var posicao_no_ranking = {};

for (var posicao = 1; posicao <= n; posicao++) {
  var atleta;
  scanf("%d", "atleta");
  posicao_no_ranking[atleta] = posicao;
}

for (var atleta = 1; atleta <= n; atleta++) {
  printf("%d\n", posicao_no_ranking[atleta]);
}
