

var n, q;
scanf("%d%d", "n", "q");
query = new Array(q);
for(var i =0; i < q; i++){
    query[i] = new Array(4);
}
last = new Array(n);
for(var i =0; i < n; i++){
    last[i] = 0;
}
for(var i=0;i<q;i++){
    var op;
    scanf("%d", "op");
    if(op == 1){
        var a, b, w, x;
        scanf("%d%d%d", "a", "b", "x");
        w = x;
        a--, b--;
        last[a] = last[b] = i;
        query[i] = {0:1, 1:a, 2:b, 3:w};
    }  
    else{
        var v;
        scanf("%d", "v");
        v--;
        query[i] = {0:2, 1:v, 2:-1, 3:-1};
    }
}
ans = new Array(n);
sum = new Array(n);
for(var i =0; i < n; i++){
    ans[i] = BigInt(0);
    sum[i] = 0;
}
sz = new Array(n);
p = new Array(n);
for(var i=0;i<n;i++) p[i] = i, sz[i] = 1;

function find(u){
    while(p[u] != u){
        if(p[p[u]] != p[u])
            p[u] = p[p[u]];
        u = p[u];
    }
    return u;
}

function join(u, v, w){
    u = find(u);
    v = find(v);
    ans[u] = ans[u] + ans[v] + BigInt(sum[u]) * BigInt(sz[v]) + BigInt(sum[v]) * BigInt(sz[u]) + BigInt(w) * BigInt(sz[u]) * BigInt(sz[v]);
    sum[u] = sum[u] + sum[v] + w * sz[v];
    sz[u] = sz[u] + sz[v];
    p[v] = u;
}

for(var i =0; i <q; i++){
    var op = query[i][0];
    var a = query[i][1];
    var b = query[i][2];
    var w = query[i][3];
    
    if(op == 1){
        if(last[a] < last[b]){
            var tmp = a;
            a = b;
            b = tmp;
        }
        join(a, b, w);
    }
    else if(op == 2){
        var v = find(a);
        printf("%s\n", ans[v]);
    }
}    

return 0;
