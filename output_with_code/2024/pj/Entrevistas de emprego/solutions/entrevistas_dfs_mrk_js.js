/*
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - modela os grupos de amigos como componentes conexas
      de um grafo. Faz DFS para identificar os grupos de amigos
    - usa vetor de marcação para ver se alguma componente
      aparece mais de uma vez em uma entrevista
*/

var n;
scanf("%d", "n");

var tabela = Array(n);
for (var i = 0; i < n; i++) {
    tabela[i] = Array(n);
    scanf("%s", "tabela[i]");
}

var componente = Array(n);
for (var i = 0; i < n; i++) {
    componente[i] = false;
}
function dfs(v, c) {
    componente[v] = c;
    for (var w = 0; w < n; w++) {
        if (componente[w] || tabela[v][w] == '0') continue;
        dfs(w, c);
    }
}

var comp_atual = 1;
for (var i = 0; i < n; i++) {
    if (!componente[i]) {
        dfs(i, comp_atual);
        comp_atual++;
    }
}

var e;
var mrk = Array(n + 1);
var candidato = Array(n);
for (var j = 0; j <= n; j++) {
    mrk[j] = false;
}
scanf("%d", "e");
for (var i = 0; i < e; i++) {
    var k;
    scanf("%d", "k");
    var possui_amigos = false;
    for (var j = 0; j < k; j++) {
        scanf("%d", "candidato[j]");
        // estamos indexando do zero
        candidato[j] -= 1;
        var repr_atual = componente[candidato[j]];
        if (mrk[repr_atual]) {
            possui_amigos = true;
        }
        mrk[repr_atual] = true;
    }
    for (var j = 0; j < k; j++) {
        var repr_atual = componente[candidato[j]];
        mrk[repr_atual] = false;
    }
    if (possui_amigos) {
        printf("S\n");
    } else {
        printf("N\n");
    }
}
