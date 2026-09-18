/*
OBI 2024 - Fase 3
  Entrevistas de Emprego
  Solução em O(N^2 + E * N):
    - define o representante de cada grupo de amigos
      como o menor ID no grupo
    - usa vetor de marcação para ver se algum representante
      aparece mais de uma vez em uma entrevista
*/

import java.util.*;
import java.io.*;

public class entrevistas {
  public static void main(String[] args) throws IOException {
    // Leitura rápida com BufferedReader no lugar de Scanner.
    // Não era necessário para ganhar todos os pontos da tarefa,
    // mas é recomendado para problemas com entrada grande como esse.
    BufferedReader br = new BufferedReader(
        new InputStreamReader(System.in));

    int n = Integer.parseInt(br.readLine());
    char[][] tabela = new char[n][];
    for (int i = 0; i < n; i++) {
        tabela[i] = br.readLine().toCharArray();
    }

    // representante de um candidato == o amigo dele de menor ID;
    // dois candidatos são amigos se e somente se possuem
    // o mesmo representante
    int[] representante = new int[n];
    for (int i = 0; i < n; i++) {
        representante[i] = i;
        for (int j = 0; j < i; j++) {
            if (tabela[i][j] == '1' && representante[i] == i) {
                representante[i] = j;
            }  
        }
    }

    boolean[] mrk = new boolean[n];
    for (int i = 0; i < n; i++) {
        mrk[i] = false;
    }

    int e = Integer.parseInt(br.readLine());
    int[] candidato = new int[n];
    while (e > 0) {
        e--;
        String[] line = br.readLine().split(" ");
        int k = Integer.parseInt(line[0]);

        boolean possui_amigos = false;

        for (int i = 0; i < k; i++) {
            // estamos indexando do zero
            candidato[i] = Integer.parseInt(line[i + 1]) - 1;
        }

        for (int i = 0; i < k; i++) {
            if (mrk[representante[candidato[i]]]) {
                possui_amigos = true;
            }
            mrk[representante[candidato[i]]] = true;
        }

        for (int i = 0; i < k; i++) {
            mrk[representante[candidato[i]]] = false;
        }

        if (possui_amigos) {
            System.out.println("S");
        } else {
            System.out.println("N");
        }
    }
  }
}
