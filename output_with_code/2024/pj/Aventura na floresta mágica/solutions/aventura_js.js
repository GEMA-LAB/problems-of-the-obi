var dir = [
    [0, 1],
    [1, 0],
    [0, -1],
    [-1, 0]
];


var x = 0, y = 0;
var delta = 0;
var t;
scanf("%d", "t");
while(t > 0){
    t--;
    var comando;
    scanf("%s", "comando")
    if(comando == 'M'){
        var N;
        scanf("%d", "N");
        x += dir[delta][0] * N;
        y += dir[delta][1] * N;
    }
    if(comando == 'G'){
        var P;
        scanf("%d", "P");
        P /= 90;
        delta = (delta + P) % 4;
    }
}
printf("%d %d", x, y);

