/*
OBI 2024 - Fase 3
  Amigos
  Solução em O(N)

  A observação principal neste problema é de nunca é
  ótimo um integrante do grupo fazer uma troca com um
  outro integrante do grupo (pois essa troca não mudaria
  em nada as posições dos integrantes). Portanto, os
  integrantes em cada lado da mesa se mantêm sempre na
  mesma ordem (entre eles) que estavam no início.

  Assim, o seguinte algoritmo guloso funciona:
  Pareie os integrantes em cada lado da esquerda para
  a direita, ou seja: o primeiro integrante do lado
  superior com o primeiro do lado inferior, o segundo
  do lado superior com o segundo do lado inferior, e
  assim em diante. Basta então somar as distâncias
  de cada par.

  Uma prova formal de que o algoritmo guloso está
  correto pode ser feita com argumento de troca.
*/

import java.util.*;

public class amigos {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int n = scanner.nextInt();
    int k = scanner.nextInt();
    int[] a = new int[n];
    int[] b = new int[n];
    for (int i = 0; i < n; i++) {
      a[i] = scanner.nextInt();
    }
    for (int i = 0; i < n; i++) {
      b[i] = scanner.nextInt();
    }

    scanner.close();

    // a resposta pode exceder o limite de valor de um int,
    // então usamos o tipo long
    long resp = 0;
    int pos_b = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == 0) continue;
      while (b[pos_b] == 0) pos_b++;
      // encontrei um par de integrantes
      resp += Math.abs(i - pos_b);
      pos_b++;
    }
    
    System.out.println(resp);
  }
}
