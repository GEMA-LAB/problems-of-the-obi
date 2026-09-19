var N, M, K;
scanf("%d %d %d", "N", "M", "K")
var P = []
for(let i = 0; i < N; i++){
    var x;
    scanf("%d","x")
    P.push(x)
}
var left = 0, right = 100001;
while(left + 1 < right){
    var mid = (left + right) >> 1;
    var groups = 0;
    var cur = 0;
    for(let i =0; i < N; i++){
        if(P[i] < mid){
            cur++;
        }
        if(cur == M){
            groups++;
            cur = 0;
        }
    }
    if(groups >= K)
        right = mid;
    else
        left = mid;
}
if(right == 100001)
    right = -1;
printf("%d\n", right);
