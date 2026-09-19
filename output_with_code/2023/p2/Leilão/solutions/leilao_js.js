// OBI2023                                                                                                                                         // Tarefa Leilão                                                                                                                                   // r. anido                                                                                                                                        

var n;

scanf("%d", "n");

var melhor_valor = 0;
var melhor_nome = "";

for (var i=0; i<n; i++) {
    var nome, valor;
    scanf("%s", "nome");
    scanf("%d", "valor");

    if (valor > melhor_valor) {
        melhor_valor = valor;
        melhor_nome = nome;
    }
}

printf("%s\n", melhor_nome);
printf("%d\n", melhor_valor);
