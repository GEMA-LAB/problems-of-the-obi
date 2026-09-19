// celular                                                                                                                                                                             
// obi2020 fase 3                                                                                                                                                                       

function sq(x) {
   return x*x;
}

var MAX = 10000;
var X=[MAX], Y=[MAX], N, A;
var adj=[MAX];
var marcado=[MAX];

function dfs(idx) {
   if(marcado[idx])return;
   marcado[idx] = 1;
   for(var i = 0; i < adj[idx].length; i++)
      dfs(adj[idx][i]);
}

// le entrada
scanf("%d","N");
for(var i = 0; i < N; i++)
    scanf("%d%d","X[i]","Y[i]");
scanf("%d","A");
A *= A;

for (var i = 0; i < N; i++)
    adj[i] = [0];

for(var i = 0; i < N; i++){
   for(var j = i+1; j < N; j++){
      if(sq(X[i]-X[j])+sq(Y[i]-Y[j]) <= A) {
         adj[i].push(j);
         adj[j].push(i);
      }
   }
}
for (var i = 0; i < N; i++)
    marcado[i] = 0;

// verifica se conexo
dfs(0);

var ok = true;
for (var i = 0; i < N && ok; i++)
    ok &= marcado[i];

if (ok)
   printf("S\n");
else
   printf("N\n");
