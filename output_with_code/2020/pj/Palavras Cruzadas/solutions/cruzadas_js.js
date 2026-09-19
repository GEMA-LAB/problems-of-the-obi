// OBI2020
// palavras cruzadas

var horizontal=[];
var vertical=[];
var total = 0;
var ok = true;
var indice_h = -1, indice_v = -1;

scanf("%s", "horizontal");
scanf("%s", "vertical");


for (var i=horizontal.length-1; i>=0; i--) {
    for (var j=vertical.length-1; j>=0; j--) {
	if (horizontal[i] == vertical[j]) {
	    indice_h = i+1;
	    indice_v = j+1;
	    ok = false;
	    break;
	}
    }
    if (!ok)
	break;
}

printf("%d %d\n", indice_h, indice_v);
