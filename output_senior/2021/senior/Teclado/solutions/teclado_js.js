// OBI2021 - Fase3
// Teclado


var repr = {'2': 'abc',
        '3': 'def',
        '4': 'ghi',
        '5': 'jkl',
        '6': 'mno',
        '7': 'pqrs',
        '8': 'tuv',
        '9': 'wxyz'};
var num, m;

scanf("%s", "num");
scanf("%s", "m");

var resp = 0;
for (var i=0; i<m; i++) {
    var palavra;
    scanf("%s", "palavra");

    // se têm comprimentos diferentes não é representação correta
    if (palavra.length != num.length)
	continue;
    var ok = true;
    // para cada letra da palavra, verifica se é representação correta
    for (var k=0; k<num.length; k++) {
	if (!repr[num[k]].includes(palavra[k])) {
            ok = false;
            break;
	}
    }
    if (ok)
	resp++;
}

// imprime resposta
printf("%d\n", resp);
