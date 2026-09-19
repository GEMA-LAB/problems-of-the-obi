// OBI2021 - Fase3
// Sr. Sapo

var L, C, P;

scanf("%d%d", "C", "L");

var lago = [C+1],
    visitado = [C+1];

for (var j=0; j<=C; j++) {
    lago[j] = [L+1];
    visitado[j] = [L+1];
}

for (var j=0; j<=L; j++) {
    for (var i=0; i<=C; i++) {
 	lago[i][j] = false;
 	visitado[i][j] = false;
    }
}

scanf("%d", "P");

for (var i = 0; i < P; i++) {
    var col, lin;
    scanf("%d%d", "col", "lin");
    lago[col][lin] = true;
}
  
var c_ini, l_ini, c_dest, l_dest;
scanf("%d%d", "c_ini", "l_ini");
scanf("%d%d", "c_dest", "l_dest");

// BFS
var q = [];
q.push( [c_ini,l_ini] );

var resp = "N";
while ( q.length > 0 ) {
    var l = q.pop();
    var i = l[0];
    var j = l[1];
    
    if (i == c_dest && j == l_dest) {
	resp = "S";
	break;
    }
    
    if (!visitado[i][j]) {
	visitado[i][j] = true;
	
	// possiveis pulos
	var a, b;
	for (var dist = 1; dist <= 3; dist++) {
	    a = i + dist; b = j;
	    if ( a <= C && lago[a][b] && !visitado[a][b] )
		q.push( [a,b] );
	    a = i - dist; b = j;
	    if ( a > 0 && lago[a][b] && !visitado[a][b] )
		q.push( [a,b] );
	    a = i; b = j + dist;
	    if ( b <= L && lago[a][b] && !visitado[a][b] )
		q.push( [a,b] );
	    a = i; b = j - dist;
	    if ( b > 0 && lago[a][b] && !visitado[a][b] )
		q.push( [a,b] );
	}
    }
}
printf("%s\n", resp);
