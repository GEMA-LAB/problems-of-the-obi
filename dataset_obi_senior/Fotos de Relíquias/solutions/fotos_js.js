var n;
scanf("%d", "n");

var arr = Array(n).fill(0);

for (var i = 0; i < n; i++) {
  scanf("%d", "arr[i]");
}

var prev = -1, ptr = 0;
while (ptr < n && arr[ptr] == 0) {
  ptr++;
}

var ans = 0;
while (ptr < n) {
  var curr = ptr;
  ptr++;

  while (ptr < n && arr[ptr] == 0) {
    ptr++;
  }

  ans += (curr - prev) * (ptr - curr);
  prev = curr;
}

printf("%d\n", ans);
