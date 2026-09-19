var gols = [];
var p;
scanf("%d", "p");
for(var i = 1; i <= p; i++) {
	var t;
	scanf("%d", "t");
	gols[t] = 1;
}
var c;
scanf("%d", "c");
for(var i = 1; i <= c; i++) {
	var t;
	scanf("%d", "t");
	gols[t] = 2;
}
var placar = [0, 0, 0];
printf("%d %d\n", placar[1], placar[2]);
for(var t = 1; t <= 100; t++) {
	if(gols[t] != undefined) {
		placar[gols[t]]++;
		printf("%d %d\n", placar[1], placar[2]);
	}
}