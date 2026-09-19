
var N, F;
scanf("%d", "N");
scanf("%d", "F");
M = new Array(N);

for(var i = 0; i < N; i++){
    scanf("%d", "M[i]");
}



P = new Array(F);
for(var i = 0; i < F; i++)
    scanf("%d", "P[i]");

B = new Array(F);
for(var i = 0; i < F; i++)
    scanf("%d", "B[i]");

for (var i = 0; i < F; ++i) {
    for (var j = i+1; j < F; ++j) {
        if (P[i] > P[j]) {
            var aux = P[i];
            P[i] = P[j];
            P[j] = aux;
            aux = B[i];
            B[i] = B[j];
            B[j] = aux;
        }
    }
}

for (var i = 0; i < N; ++i) {
    for (var j = i+1; j < N; ++j) {
        if (M[i] > M[j]) {
            var aux = M[i];
            M[i] = M[j];
            M[j] = aux;
        }
    }
}

for (var i = 0; i < F; ++i) {
    var first_alive = N;
    for (var j = 0; j < N; ++j) {
        if (M[j] > 0) {
            first_alive = j;
            break;
        }
    }
    for (var j = first_alive; j < N && B[i] > 0; ++j) {
        if (P[i] > M[j]) {
            M[j] = 0;
            B[i] -= 1;
        }
    }
}

var cnd = 0;
for (var i = 0; i < N; ++i) {
    if (M[i] == 0) cnd += 1;
}

printf("%d\n", cnd);

