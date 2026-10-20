// OBI2021 - Fase 2                                                                                                          
// Senha

var n, m, k, x, tmp;
var s = [];
var palavras = [];
var pos = [];

scanf("%d %d %d", "n", "m", "k");
scanf("%s", "tmp");
s = tmp.split('');

for (var i = 0; i < m; i++) {
    scanf("%s","tmp");
    palavras[i] = tmp.split('');
}

scanf("%d", "x");

for (var i = 0; i < n; i++)
    if (s[i] == '#')
        pos.push(i);

if (m == 1) {
   palavras[0].sort();
   s[pos[0]] = palavras[0][x - 1];
   printf("%s\n", s.join(''));
}
else {
   x--;
   for (var i = 0; i < m; i++)
      palavras[i].sort();
   for (var i = 0; i < m; i++)
      s[pos[i]] = palavras[i][0];
   for (var i = m - 1; i >= 0; i--) {
      if (x == 0)
         break;
      tmp = x % k;
      s[pos[i]] = palavras[i][tmp];
      x = Math.floor(x/k);
   }
   printf("%s\n", s.join(''));
}
