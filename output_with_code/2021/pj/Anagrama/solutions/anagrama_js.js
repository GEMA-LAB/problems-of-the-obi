// OBI2021 - Fase 2
// Anagrama

var n, x;
var letras1 = [];
var letras2 = [];

scanf("%d\n", "n");
for (var i = 0; i < n; ++i) {
    scanf("%c", "x");
    if (x != ' ' && x != ',' && x != '.')
	letras1.push(x);
}
// como estamos lendo caractere por caractere,
// precisamos ler o caractere final de linha
scanf("%c", "x");

for (var i = 0; i < n; ++i) {
    scanf("%c", "x");
    if (x != ' ' && x != ',' && x != '.')
	letras2.push(x);
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
