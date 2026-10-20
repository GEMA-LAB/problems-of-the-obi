var n;
scanf("%d", "n");

var instrucoes;
scanf("%s", "instrucoes");

var sala = 1;

// passa pelas instruções em ordem, atualizando a sala a cada passo
for (var i = 0; i < n; i++) {
  if (instrucoes[i] == 'E') {
    sala = 2 * sala;
  } else {
    sala = 2 * sala + 1;
  }
}

printf("%d\n", sala);
