// piso de atlanta
// obi2020 - fase 3

var a, b,
    tmp_larg, tmp_compr,
    larg=-1, compr=-1;

scanf("%d%d","a","b");

for (var x = 1; x <= b; x++) {
    if (b % x != 0)
	continue;
    tmp_larg = b/x + 2;
    tmp_compr = x + 2;
    if (a == 2*(tmp_compr + tmp_larg) - 4) {
	compr = tmp_compr;
	larg = tmp_larg;
	break;
    }
}

printf("%d %d\n", compr, larg);
