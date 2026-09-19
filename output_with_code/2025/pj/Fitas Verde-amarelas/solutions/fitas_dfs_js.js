
var n, m;
scanf("%d %d", "n", "m");

var grid = Array(n);
var comp = Array(n);
var comp_atual = 0;

for (var i = 0; i < n; i++) {
    grid[i] = Array(m);
    scanf("%s", "grid[i]");
    comp[i] = Array(m).fill(0);
}


const dl = [-1, 0, 1, 0];
const dc = [0, 1, 0, -1];

// busca em profundidade
function dfs(l, c) {
  comp[l][c] = comp_atual;
  for (var i = 0; i < 4; i++) {
    var nl = l + dl[i];
    var nc = c + dc[i];
    if (nl < 0 || nl >= n || nc < 0 || nc >= m) continue;
    if (grid[nl][nc] == '#' && comp[nl][nc] == 0) {
      dfs(nl, nc);
    }
  }
}

// encontra componentes conexas
for (var l = 0; l < n; l++) {
    for (var c = 0; c < m; c++) {
      if (grid[l][c] == '#' && !comp[l][c]) {
        comp_atual++;
        dfs(l, c);
      }
    }
}


// testa colocar fitas horizontais em cada componente
var fitas_hor = Array(comp_atual + 1).fill(0);
for (var l = 0; l < n; l++) {
    for (var c = 0; c < m; c++) {
      if (grid[l][c] != '#') continue;
      if (c == 0 || grid[l][c - 1] != '#') {
        fitas_hor[comp[l][c]]++;
      }
    }
}

// testa colocar fitas verticais em cada componente
var fitas_ver = Array(comp_atual + 1).fill(0);
for (var c = 0; c < m; c++) {
    for (var l = 0; l < n; l++) {
      if (grid[l][c] != '#') continue;
      if (l == 0 || grid[l - 1][c] != '#') {
        fitas_ver[comp[l][c]]++;
      }
    }
}


// pega a melhor opcao pra cada componente
var resp = 0;
for (var i = 1; i <= comp_atual; i++) {
    resp += Math.min(fitas_hor[i], fitas_ver[i]);
}

printf("%d\n", resp)
