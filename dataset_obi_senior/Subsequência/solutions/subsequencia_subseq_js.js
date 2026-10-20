// OBI2023
// Tarefa Subsequencia
// r. anido

var na, nb;

scanf ("%d %d", "na", "nb");

var a = [];
var b = [];

for (var i=0; i<na; i++) {
   var x;
   scanf("%d", "x");
   a.push(x);
}

for (var i=0; i<nb; i++) {
   var x;
   scanf("%d", "x");
   b.push(x);
}


var resp = "S";
var i = 0, j = 0;

while (true) {
    if (a[i] == b[j]) {
	i += 1;
	j += 1;
    }
    else {
	i += 1;
    }
    
    if (j == b.length)
	break;
    if (i == a.length) {
	resp = "N";
	break;
    }
}


printf("%s\n", resp);
