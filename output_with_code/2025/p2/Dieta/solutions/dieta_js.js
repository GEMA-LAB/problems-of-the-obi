
/*
  OBI 2025 - Fase 1
  Dieta
*/


var n, m; 
scanf("%d %d", "n", "m");

var calorias = 0;
for( var i = 0; i < n; i++ ){
    var p, g, c; 
    scanf("%d %d %d", "p", "g", "c" ); 
    calorias += 4*p + 9*g + 4*c;
}

var total = m - calorias;

printf("%d", total);