// OBI2021
// Tarefa Zero para Cancelar

var n, comando;
var lista=[];

scanf("%d","n");

// lê e processa os comandos
var num = 0;
for (var i=0; i<n; i++){
    scanf("%d","comando");
    if (comando == 0) // cancela último, retira da lista
	num--;
    else { // adiciona comando à lista
	lista[num] = comando;
	num++;
    }
}

// soma os que restaram na lista
var total = 0;
for (var i=0; i<num; i++)
    total = total + lista[i];

printf("%d\n", total);

