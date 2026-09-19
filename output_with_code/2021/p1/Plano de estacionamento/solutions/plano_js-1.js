// OBI2021 - Fase 3
// Plano de ação


var n, m, total=0;

scanf("%d%d", "n", "m");

var vagas = [n+1];

for (var i=0; i<=n; i++)
    vagas[i] = 0;

var ok = true;
for (var i=0; i<m && ok; i++) {
    var plano;
    scanf("%d", "plano");
    
    while (plano > 0 && vagas[plano] > 0) {
	var t = vagas[plano];
	vagas[plano]++;
	plano -=  t;
    }
    if (plano <= 0)
	ok = false;
    else {
	vagas[plano] = 1;
	total++;
    }
}

printf("%d\n", total);

