// OBI2021                                                                                                                                                                                               
// Pangrama                                                                                                                                                                                               

var letras = new Set();
var letra;

// lê a linha e constrói o conjunto de caracteres
while (true) {
    scanf("%c","letra");
    if (letra=='\n')
	break;
    letras.add(letra);
}

// remove do conjunto caracteres que não são letras
letras.delete(' ');
letras.delete(',');
letras.delete(':');

// imprime o resultado
if (letras.size == 23)
	printf("S\n");
else
	printf("N\n");
