/*
  OBI 2025 - Fase 1
  Festa
*/

function max( a, b ){
  if( a > b ) return a; 
  return b;
}

function min( a, b ){
  if( a > b ) return b; 
  return a;
}

var e, s, m; 
scanf("%d", "e");
scanf("%d", "s");
scanf("%d", "m");

var maior = max( e, max( s, m )); 
var menor = min( e, min( s, m )); 

printf("%d", 2*(maior - menor)); 