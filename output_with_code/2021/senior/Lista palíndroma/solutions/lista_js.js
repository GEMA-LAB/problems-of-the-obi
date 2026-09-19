// OBI2021 - Fase 2
// Lista palíndroma

var n;
var lista = [];

scanf("%d", "n");
for (var i = 0; i < n; ++i) 
    scanf("%d", "lista[i]");

var sol = 0, p_esq = 0, p_dir = n - 1;

while (p_esq < p_dir) {
    if (lista[p_esq] == lista[p_dir]) {
      ++p_esq; --p_dir;
      continue;
    }
    if (lista[p_esq] < lista[p_dir]) {
      lista[p_esq + 1] += lista[p_esq];
      ++p_esq;
    } else {
      lista[p_dir - 1] += lista[p_dir];
      --p_dir;
    }
    ++sol;
}

printf("%d\n", sol);
