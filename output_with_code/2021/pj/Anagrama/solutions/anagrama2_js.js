// OBI2021 - Fase 2
// Anagrama

var n;
var letra;
var letras1 = [];
var letras2 = [];

scanf("%d\n", "n");

while (true) {
    scanf("%c","letra");
    if (letra=='\n')
	break;
    if (letra != ' ' && letra != ',' && letra != '.')
	letras1.push(letra);
}

while (true) {
    scanf("%c","letra");
    if (letra=='\n')
	break;
    if (letra != ' ' && letra != ',' && letra != '.')
	letras2.push(letra);
}


res = "S";
if (letras1.length != letras2.length) {
    res = "N";
}
else {
    letras1.sort();
    letras2.sort();
    
    for (i=0; i<letras1.length; i++) {
	if (letras1[i] != letras2[i]) {
            res = "N";
            break;
        }
    }
}

printf("%s\n", res);

