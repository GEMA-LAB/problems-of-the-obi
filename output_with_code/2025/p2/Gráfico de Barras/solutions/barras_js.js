/*
  OBI 2025 - Fase 1
  Grafico
*/

var n;
scanf("%d", "n");

const v = [];

var maior = 0;

for( var i = 0; i < n; i++ ){
    var x; scanf("%d", "x");
    v[i] = x;
    if( v[i] > maior ) maior = v[i];
}

const matriz = [];

for( var i = 0; i < maior; i++ ) matriz[i] = [];

for( var i = 0; i < n; i++ ){
    for( var j = 0; j < maior; j++ ){
        if( j >= maior - v[i] ) matriz[j].push(1); 
        else matriz[j].push(0);
    }
}
    
for( var i = 0; i < maior; i++ ){
    for( var j = 0; j < n; j++ ){
        printf("%d ", matriz[i][j]); 
    }
    printf("\n")
}