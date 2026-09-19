////                                                                                                                        
// Pandemia - OBI2020
// r.anido
////

var n, m;
var i, dia, a;

scanf("%d%d","n","m");
scanf("%d%d","i","dia");

var infectados = new Set([i]);
for (var d=1; d<=m; d++) {
    scanf("%d","a");
    contagio = false;
    amigos = [];
    for (var k=0; k<a; k++) {
	scanf("%d","x");
        amigos.push(x);
	if (infectados.has(x))
            contagio = true;
    }
    if (d >= dia && contagio) {
	for (var k=0; k<amigos.length; k++) {
	    infectados.add(amigos[k]);
        }	
    }
}

printf("%d\n",infectados.size);
