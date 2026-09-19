

/*
  OBI 2025 - Fase 1
  Fila
*/


var n;
scanf("%d", "n"); 

const v = [];
for( var i = 0; i < n; i++ ){
    var x; scanf("%d", "x"); 
    v[i] = x
}

var maior = -1, resp = 0;
for( var i = n - 1; i >= 0; i-- ){
    if( v[i] <= maior ) resp++; 
    else maior = v[i]; 
}

printf("%d", resp)