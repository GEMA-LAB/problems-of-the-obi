/*
OBI 2024 - Fase 3
  Musical
  Solução em O(N log N)

  A observação chave para resolver este problema é a seguinte:
  Dado um intervalo qualquer de músicas distintas, a menor dissonância
  é obtida ao ordenarmos as músicas em ordem crescente ou em ordem
  decrescente de energia, e essa dissonância é
      maior_energia - menor_energia.
  Para visualizar isso, você pode desenhar um gráfico com as energias
  atuais. Uma prova formal pode ser feita com argumento de troca.

  Sabendo disso, temos um limite mínimo para a resposta:
  considerando as músicas de menor e maior energia, existem dois
  intervalos na lista circular que possuem essas duas músicas como
  pontas (o que vai da menor pra maior energia e o que vai da maior
  para a menor), logo, a resposta é no mínimo
    2 * (maior_energia - menor_energia).
  Claramente, este mínimo é atingido se ordenarmos cada um desses
  dois intervalos.
*/

var n;
scanf("%d", "n");

var energias = Array(n);
for (var i = 0; i < n; i++) {
  scanf("%d", "energias[i]");
}

energias.sort((x, y) => x - y);
var maior = energias[n - 1];
var menor = energias[0];

printf("%d\n", 2 * (maior - menor));
