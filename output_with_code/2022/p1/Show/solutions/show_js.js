// OBI2022
// Tarefa ingressos

var a, n, m;
var assento;

scanf("%d%d%d","a","n","m");

var melhor_fila = n+1;

for (var fila=n; fila > 0; fila--) {
    var contiguos = 0;
    for (var i=0; i < m; i++) {
        scanf("%d", "assento");
        if (assento === 0) {
            contiguos++;
            if (contiguos >= a) {
                // amigos cabem nesta fila
                if (fila < melhor_fila) 
                    melhor_fila = fila;
            }
        }
        else
            contiguos = 0;
    }
}

if (melhor_fila == n+1)
    printf("-1\n");
else
    printf("%d\n",melhor_fila);

