//////
// problema escher, OBI2020
//////

var n, perfil=[];

// leitura dos dados
scanf("%d", "n");
for (i=0; i<n; i++) {
    scanf("%d","perfil[i]");
}

// varre o vetor com um índice a partir do início (i)
// e um índice a partir do final do vetor (j)
var i=0, j=n-1;
var escher = 'S';
var altura = perfil[i] + perfil[j];
while (i <= j) {
    if (perfil[i]+perfil[j] != altura) {
        escher = 'N';
        break;
    }
    i += 1;
    j -= 1;
}

// imprime o resultado
printf("%s\n",escher);
