/**
 * OBI 2023 - Fase 3
 * Balanceamento de Pirâmide - Solução com ordenação e força bruta
 * Mateus Bezrutchka
 **/

// lê numeros em um vetor e guarda a soma
var v = Array(6);
var soma = 0;
for (var i = 0; i < 6; i++) {
  scanf("%d", "v[i]");
  soma += v[i];
}

// se a soma nao é divisivel por 3, é impossivel
if (soma % 3 != 0) {
  printf("N\n");
  return;
}

// ordenação por valor numerico
v.sort(function(a, b) { return a - b });

// o maior valor deve estar no terceiro andar
if (v[5] != soma / 3) {
  printf("N\n");
  return;
}

// temos que achar outros dois pro segundo andar
for (var i = 0; i < 5; i++) {
  for (var k = i + 1; k < 5; k++) {
    if (v[i] + v[k] == soma / 3) {
      printf("S\n");
      return;
    }
  }
}

// se chegamos aqui, nao achamos par pro segundo andar
printf("N\n");

