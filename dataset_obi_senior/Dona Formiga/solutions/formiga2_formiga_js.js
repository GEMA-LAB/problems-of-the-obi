const MAX = 200;

var S, T, P;
var altura = [];
var visitado = [];
var adj = [];
var alcancados = 0;

function busca(k) {
    if (!visitado[k]) {
	alcancados++;
	visitado[k] = 1;	
	adj[k].forEach(q => busca(q));
    }
}

scanf("%d%d%d", "S", "T", "P");
for (var i=0; i<S; i++) {
    scanf("%d", "altura[i]");
    adj[i] = [];
}

var a, b;
for (var i=0; i<T; i++) {
    scanf("%d%d", "a", "b");
    a--; b--;
    if (altura[a] > altura[b])
	adj[a].push(b);
    else if (altura[a] < altura[b])
	adj[b].push(a);
}

busca(P-1);
printf("%d\n", alcancados-1);
