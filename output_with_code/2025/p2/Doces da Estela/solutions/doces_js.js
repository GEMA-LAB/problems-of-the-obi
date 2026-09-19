
var N = 0;
var preco_total = 0;

scanf("%d", "N");
for(var d = 1; d <= N; d++){
    if(N % d == 0){
        var c = N / d;
        var caixa_simples = (10 + 3 * d);
        var caixa_enfeitada = (2 + c) * caixa_simples;
        var pedido = caixa_enfeitada * c;
        preco_total += pedido;
    }
}
printf("%d\n", preco_total);

