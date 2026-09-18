
function solve(X) {
    if (X == 1) return 1;
    else if (X == 2) return 2;
    else if (X == 3) return 4;
    else if (X == 4) return 5;
    else if (X == 5) return 7;
    else {
        var ans = 13;
        while (X > 6) {
            ans += 6;
            X -= 1;
        }
        return ans;
    }
}


var X;
scanf("%d", "X");
printf("%d\n", solve(X));

