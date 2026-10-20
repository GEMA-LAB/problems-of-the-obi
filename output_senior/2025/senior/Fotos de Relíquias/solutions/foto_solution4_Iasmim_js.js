
var n = 0;
scanf("%d", "n");
let a = new Array(n).fill(0);
for(let i=0; i < n; i++){
    var aux=0;
    scanf("%d", "aux");
    a[i] = aux;
}
let f = new Array(n).fill(0);
for(let i=0; i < n; i++){
    var aux=0;
    scanf("%d", "aux");
    f[i] = aux;
}

a.push(1e9);

let ans = new Array(n).fill(0);
let psum = [0n];
let last = [1000000000n];
let sum = [0n];

for (let i = n - 1; i >= 0; i--) {
    let sz = BigInt(psum.length-1);
    let p = sz - BigInt(f[i]);

    if (sz < f[i]) ans[i] = -1n;
    else {
        let psumLast = BigInt(psum[sz]);
        let sumLast = BigInt(sum[sz]);
        ans[i] = psumLast - psum[p] - p * BigInt(sumLast - sum[p]);
    }

    while (a[i] >= last[last.length - 1]) {
        psum.pop();
        last.pop();
        sum.pop();
    }

    sz = psum.length;
    psum.push(BigInt(psum[sz - 1]) + BigInt(sz) * BigInt(a[i]));
    last.push(BigInt(a[i]));
    sum.push(BigInt(a[i]) + sum[sz - 1]);
}


for(let i=0; i < n; i++) {
    printf("%d ", ans[i]);
}
printf("\n");