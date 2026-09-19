var N, S;

scanf("%d", "N");
scanf("%d", "S");

var peguei = [];

for (var i = 0; i <= S; i++) {
    peguei.push(false);
}

var X = [];

for (var i = 0; i < N; i++) {
    var x;
    scanf("%d", "x");
    X.push(x);
}

var resposta, l, atual;

resposta = 0;
l = 0;
atual = 0;

for (var r = 0; r < N; r++) {
	while (peguei[X[r]]) {
		peguei[X[l]] = false;
		atual -= 1;
		l += 1;
	}

	peguei[X[r]] = true;
	atual += 1;
	resposta = resposta >= atual ? resposta : atual;
}

printf("%d\n", resposta);