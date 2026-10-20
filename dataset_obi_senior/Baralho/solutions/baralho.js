// OBI2021 - Fase 1
// 19477-J
// Salomão Neto Fernandes de Freitas


function duplicada(list) {
   var processed = [];
   
   for(var i = 0; i < list.length; i++) {
      var item = list[i];
      
      if (processed.includes(item)) {
         return true;
      }
      
      processed.push(item);
   }
   
   return false;
}

var entrada;
var cartas = {
	C: [],
	E: [],
	U: [],
	P: []
};

scanf("%s", "entrada");

while(entrada.length) {
   var num = entrada.substring(0, 2);
   var naipe = entrada.substring(2, 3);
   
   entrada = entrada.substring(3);
   
   cartas[naipe].push(num);
}

for (var naipe in cartas) {
   if (duplicada(cartas[naipe])) {
       printf("erro\n");
      continue;
   }
   
   printf("%d\n", 13-cartas[naipe].length);
}
