/*
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - define o representante de cada grupo de amigos
      como o menor ID no grupo
    - usa vetor de marcação para ver se algum representante
      aparece mais de uma vez em uma entrevista
*/

var n;
scanf("%d", "n");

var tabela = Array(n);
for (var i = 0; i < n; i++) {
    tabela[i] = Array(n);
    scanf("%s", "tabela[i]");
}

// representante de um candidato == o amigo dele de menor ID;
// dois candidatos são amigos se e somente se possuem
// o mesmo representante
var representante = Array();
for (var i = 0; i < n; i++) {
    representante.push(i);
    for (var j = 0; j < i; j++) {
        if (tabela[i][j] == '1' && representante[i] == i) {
            representante[i] = j;
        }
    }
}

var e;
var mrk = Array(n);
var candidato = Array(n);
for (var i = 0; i < n; i++) {
    mrk[i] = false;
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
        var repr_atual = representante[candidato[j]];
        if (mrk[repr_atual]) {
            possui_amigos = true;
        }
        mrk[repr_atual] = true;
    }
    for (var j = 0; j < k; j++) {
        var repr_atual = representante[candidato[j]];
        mrk[repr_atual] = false;
    }
    if (possui_amigos) {
        printf("S\n");
    } else {
        printf("N\n");
    }
}
