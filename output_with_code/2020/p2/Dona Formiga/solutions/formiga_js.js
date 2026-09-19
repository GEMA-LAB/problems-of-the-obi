const MAX = 200;

var S, T, P;
var altura = [];
var distancia = [];
var adj = [];

function busca(k) {
    if (distancia[k] == -1) {
	distancia[k] = 0;
	adj[k].forEach(q =>
	    distancia[k] = Math.max(1 + busca(q), distancia[k]));
    }
    return distancia[k]
}

scanf("%d%d%d", "S", "T", "P");
for (var i=0; i<S; i++) {
    scanf("%d", "altura[i]");
    distancia[i] = -1;
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


printf("%d\n", busca(P-1));
