const  MAX = 505;
const  MIN = -1e9;

var n;
var elem_linha0, elem_linha1;
var linha0=[], linha1=[];
var tab=[];

function pd() {
    var uma = 1;
    var outra = 1 - uma;
    for (var i=0; i<=elem_linha0; i++)
	for (var j=0; j<=elem_linha1; j++) 
	    tab[uma][i][j] = MIN;

    tab[uma][elem_linha0][elem_linha1] = 0;
    tab[outra][elem_linha0][elem_linha1] = 0;

    for (var k=0; k<n; k++) {
	for (var i=elem_linha0; i>=0; i--) {
	    for (var j=elem_linha1; j>=0; j--) {
		if (i == elem_linha0 && j == elem_linha1)
		    continue;
		tab[outra][i][j] = MIN;
		if (i < elem_linha0)
		    tab[outra][i][j] = Math.max(tab[outra][i][j], tab[uma][i+1][j]);
		if (j < elem_linha1)
		    tab[outra][i][j] = Math.max(tab[outra][i][j], tab[uma][i][j+1]);
		if (i < elem_linha0 && j < elem_linha1)
		    tab[outra][i][j] = Math.max(tab[outra][i][j],linha0[i]*linha1[j] + tab[uma][i+1][j+1]);
	    }
	}
	uma = 1 - uma;
	outra = 1 - uma;
    }
    return tab[uma][0][0];
}


scanf("%d", "n");
for (var i=0; i<2; i++) {
    tab[i] = [];
    for (var j=0; j<n+1; j++)
	tab[i][j] = [];
}

scanf("%d", "elem_linha0"); 
for (var i=0; i<elem_linha0; i++)
    scanf("%d", "linha0[i]");
scanf("%d", "elem_linha1");
for (var i=0; i<elem_linha1; i++)
    scanf("%d", "linha1[i]");

printf("%d\n", pd());

