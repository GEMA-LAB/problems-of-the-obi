const MAXN = 52;
const dx = [-1, -1, -1, 0, 0, 1, 1, 1];
const dy = [-1, 0, 1, -1, 1, -1, 0, 1];

var n, q;
scanf("%d %d", "n", "q");

var state = Array(n);
var new_state = Array(n);
var input_line;
for (var i = 0; i < n; i++) {
  scanf("%s", "input_line");
  state[i] = Array.from(input_line);
  new_state[i] = Array.from(input_line);
}

function in_bounds(x, y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

function count_alive_neighbors(x, y) {
  var alive = 0;
  for (var i = 0; i < 8; i++) {
    var nx = x + dx[i];
    var ny = y + dy[i];
    if (in_bounds(nx, ny) && state[nx][ny] == '1') alive++;
  }
  return alive;
}

function step() {
  for (var i = 0; i < n; i++) {
    for (var j = 0; j < n; j++) {
      var alive_neighbors = count_alive_neighbors(i, j);
      new_state[i][j] = state[i][j];
      if (state[i][j] == '0' && alive_neighbors == 3) {
        new_state[i][j] = '1';
      }
      if (state[i][j] == '1' && (alive_neighbors < 2 || alive_neighbors > 3)) {
        new_state[i][j] = '0';
      }
    }
  }
  for (var i = 0; i < n; i++) {
    for (var j = 0; j < n; j++) {
      state[i][j] = new_state[i][j];
    }
  }
}

while (q > 0) {
  step();
  q--;
}
for (var i = 0; i < n; i++) {
  printf("%s\n", state[i].join(''));
}
