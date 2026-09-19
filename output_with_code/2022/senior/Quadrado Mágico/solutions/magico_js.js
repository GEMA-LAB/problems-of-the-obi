// OBI2022                                                                                                                                                                                                   
// Tarefa Magico                                                                                                                                                                                             


var magico = [];
var n;
var ii, jj;

scanf("%d","n");
// popula quadrado com zeros                                                                                                                                                                                 
for (var i=0; i<n; i++ ) {
    magico[i] = [];
    for (var j=0; j<n; j++ )
        magico.push(0);
}

for (var i=0; i<n; i++) {
    for (var j=0; j<n; j++ ) {
        scanf("%d", "magico[i][j]");
        if (magico[i][j] === 0) {
            ii = i;
            jj = j;
        }
    }
}

// soma correta
var soma = 0;
for (var i=0; i<n; i++) {
    if (i == ii) continue;
    for (var j=0; j<n; j++ ) {
        soma += magico[i][j];
    }
    break;
}

// soma sem o número ilegível
var s = 0;
for (var j=0; j<n; j++ ) {
   s += magico[ii][j]; 
}



printf("%d\n", soma - s);
printf("%d\n", ii+1);
printf("%d\n", jj+1);
