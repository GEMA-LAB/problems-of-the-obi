// OBI2020
// camisetas

var x, n;
var pref=[];
var prod_p;
var prod_m;

for (var i=0; i<3; i++)
    pref[i] = 0;

scanf("%d", "n");
for (var i=0; i<n; i++) {
    scanf("%d", "x");
    pref[x]++;
}
scanf("%d", "prod_p");
scanf("%d", "prod_m");

if (prod_p >= pref[1] && prod_m >= pref[2])
    printf("S\n");
else
    printf("N\n");
