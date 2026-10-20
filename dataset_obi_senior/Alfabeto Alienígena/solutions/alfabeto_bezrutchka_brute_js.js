var k, n;
var alphabet, message;
scanf("%d %d", "k", "n");
scanf("%s", "alphabet");
scanf("%s", "message");

var good_message = true;
for (var i = 0; i < n; i++) {
  var found_char = false;
  for (var j = 0; j < k; j++) {
    if (message[i] == alphabet[j]) found_char = true;
  }
  if (!found_char) good_message = false;
}

if (good_message) printf("S\n");
else printf("N\n");
