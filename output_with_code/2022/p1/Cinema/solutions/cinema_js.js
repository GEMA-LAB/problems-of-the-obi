// OBI2022
// Tarefa Cinema

var x, y;
var resp = 0;

scanf("%d%d","x","y");

if (x < 18)
    resp += 15;
else if (x < 60)
    resp += 30;
else
    resp += 20;

if (y < 18)
    resp += 15;
else if (y < 60)
    resp += 30;
else
    resp += 20;

printf("%d\n", resp);
