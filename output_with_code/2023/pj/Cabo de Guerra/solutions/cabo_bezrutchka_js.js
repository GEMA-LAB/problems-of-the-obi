/**
 * OBI 2023 - Fase 3
 * Cabo de Guerra - Solução força-bruta com loops
 * Mateus Bezrutchka
 **/

// le os 6 valores em um vetor, guardando a soma total
var x = Array(6);
var soma = 0;
for (var i = 0; i < 6; i++) {
  scanf("%d", "x[i]");
  soma += x[i];
}

// se a soma for impar, é impossivel dividir igual
if (soma % 2 == 1) {
  printf("N\n");
  return;
}

var meia_soma = soma / 2;
// precisamos encontrar (i,k) tal que a tripla (0,i,k) pode ser um time;
// testamos todas as possibilidades
for (var i = 1; i < 6; i++) {
  for (var k = i + 1; k < 6; k++) {
    if (meia_soma == x[0] + x[i] + x[k]) {
      // encontramos, ja podemos terminar o programa
      printf("S\n");
      return;
    }
  }
}

// se chegamos aqui, nao encontramos solucao
printf("N\n");

