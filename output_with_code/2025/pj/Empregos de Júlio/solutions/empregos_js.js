
// Javascript não possui um heap binário / priority queue
// em suas bibliotecas padrões, então precisamos implementar
// o heap binário manualmente.

var heap = [];

function heap_insert(x) {
  heap.push(x);
  // push up
  var i = heap.length - 1;
  while (i > 0) {
    var p = Math.floor((i - 1) / 2);
    if (heap[p] >= heap[i]) break;
    var aux = heap[p];
    heap[p] = heap[i];
    heap[i] = aux;
    i = p;
  }
}

function heap_popMax() {
  var n = heap.length;
  var top = heap[0];
  var last = heap.pop();
  if (n > 1) {
    heap[0] = last;
    // push down
    var i = 0;
    while (true) {
      var l = 2 * i + 1;
      var r = l + 1;
      var m = i;
      if (l < n && heap[l] > heap[m]) m = l;
      if (r < n && heap[r] > heap[m]) m = r;
      if (m == i) break;
      var aux = heap[m];
      heap[m] = heap[i];
      heap[i] = aux;
      i = m;
    }
  }
  return top;
}



var n, k;
scanf("%d %d", "n", "k");

var a = Array(n), b = Array(n);

for (var i = 0; i < n; i++) {
  scanf("%d", "a[i]");
}
for (var i = 0; i < n; i++) {
  scanf("%d", "b[i]");
}

var best_prefix = 0, answer = 0;
var best_suffix = Array(n + 1).fill(0);
for (var i = n - 1; i >= 0; i--) {
  best_suffix[i] = best_suffix[i + 1] + Math.max(a[i], 2 * b[i]);
  answer += Math.max(a[i], b[i]);
}

if (k == 0) {
  printf("%d\n", best_suffix[0]);
}

else {
  for (var i = 0; i < n; i++) {
    best_prefix += b[i];
    heap_insert(a[i] - b[i]);
    if (i + 1 < k) continue;
    if (heap.length > k && heap[0] >= 0) {
      best_prefix += heap_popMax();
    }
    answer = Math.max(answer, best_prefix + best_suffix[i + 1]);
  }
  printf("%d\n", answer);
}
