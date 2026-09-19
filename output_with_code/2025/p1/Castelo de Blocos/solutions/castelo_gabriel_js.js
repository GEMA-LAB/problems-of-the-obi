

var N, M, K;
scanf("%d %d %d", "N", "M", "K");

var g = []
var R = []
var apoio = []
var quebrado = []
var retirado = []
var tentar_retirar = []

for (let i = 0; i < N + 10; i++) {
  g.push([]);
  apoio.push(0);
  quebrado.push(false);
  tentar_retirar.push(false);
}

for(let i = 0; i < M; i++) {
  var a, b;
  scanf("%d %d", "a", "b");
  a--, b--;
  g[a].push(b);
  apoio[b]++;
}

for(let i = 0; i < K; i++) {
  var r;
  scanf("%d", "r");
  r--;
  R[i] = r;
  tentar_retirar[r] = true;
}

for(let r = 0; r < K; r++) {
  let i = R[r];
  if (tentar_retirar[i] && !quebrado[i]) {
    retirado[i] = true;
    var q = [];
    q.push(i);
    var head = 0;
    while (head < q.length) {
      var v = q[head];
      head++;
      for (let u of g[v]) {
        apoio[u]--;
        if (apoio[u] == 0 && !quebrado[u] && !retirado[u]) {
          quebrado[u] = true;
          q.push(u);
        }
      }
    }
  }
}

var resposta = 0;
for(let i = 0; i < N; i++) {
  if (quebrado[i]) resposta++;
}
printf("%d\n", resposta);