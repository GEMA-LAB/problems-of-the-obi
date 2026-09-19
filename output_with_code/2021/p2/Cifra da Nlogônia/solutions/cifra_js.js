// OBI2021 - Fase 1                                                                                                         // cifra 


// constrói cadeias de acordo com o enunciado
var consoante =        "bcdfghjklmnpqrstvxz";
var vogal_mais_prox =  "aaeeeiiiiooooouuuuu";
var prox_consoante =   "cdfghjklmnpqrstvxzz";
var palavra;

scanf("%s", "palavra");

var cifra = "";
for (var i=0; i<palavra.length; i++) {
    cifra = cifra + palavra[i];  // letra original: consoante ou vogal, sempre copiada                                        
    // segunda e terceira letras apenas se consoante
    var j = consoante.indexOf(palavra[i]);
    if (j >= 0)
        cifra = cifra + vogal_mais_prox[j] + prox_consoante[j];
}

printf("%s\n",cifra);
